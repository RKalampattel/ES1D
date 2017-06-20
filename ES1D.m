% 1D Electrostatic PIC code
% Script to solve the two stream instability problem, based on code by 
% Brieda (https://www.particleincell.com/2015/two-stream-instability/), in 
% turn based on Birdsall (Plasma Physics via Computer Simulation)
%
% Rahul Kalampattel, 15/06/2017

close all; clearvars; clc
% =========================================================================== %
% Setup
% =========================================================================== %

% Constants
qm = -1;        % Charge to mass ratio
wp = 1;         % Plasma frequency
e0 = 1;         % Permittivity of free space

% Simulation parameters
L = 2*pi;       % Length of simulation domain
C = 63;         % Number of cells (N-1)
N = C+1;        % Number of nodes (C+1)
h = L/C;        % Cell width/grid spacing

npCell = 15;    % Number of particles per cell (per species)
np = C*npCell;  % Total number of particles (per species)

dt = 0.1;       % Time step
tMax = 501;  	% Max number of iterations in main loop
tol = 1e-6;     % Tolerance for potential solver

% =========================================================================== %
% Initialise simulation
% =========================================================================== %

q = wp^2*(1/qm)*e0*L/(0.5*np);  % Charge (mistake in Brieda, factor of 0.5 not needed?)
m = q/qm;                       % Mass
q0 = -q;                        % Background charge

particles = zeros(2,np);        % Vector of simulation particles ([pos; vel])
v = 1;                          % Initial velocity
dx0 = 1e-4;                     % Perturbation factor

for i = 1:np
    x0 = (0.5+i-1)*L/np;        % Seed particles (uniformly distributed)
    theta = 2*pi*x0/L;
    dx = dx0*cos(theta);        % Offset from initial location
    x1 = x0+dx;
    x2 = x0-dx;
    
    % Check if particles are still in simulation domain
    if x1<0
        x1 = x1 + L;
    elseif x1>=L
        x1 = x1 - L;
    end
    if x2<0
        x2 = x2 + L;
    elseif x2>=L
        x2 = x2 - L;
    end
    
    % Initialise particle state
    particles(:,2*i-1) = [x1; v];
    particles(:,2*i) = [x2; -v];
end

np = np*2;          % Update to take both species into account
E = zeros(1,N);     % Initialise electric field
t = 0;              % Time step counter (simulation time = t*dt)

% For plotting
fig = figure;
colormap jet;
colors = zeros(1,np);
colors(2:2:end)=1;
filename = 'testAnimated.gif';

% =========================================================================== %
% Main loop
% =========================================================================== %

while t<tMax
    rho = zeros(1,N);   % Clear the charge density vector
    
    % Find charge at grid nodes (weighting)
    for i = 1:np
        % Coordinate of grid node to the left of particle
        coord = 1 + floor(particles(1,i)/h);    
        % Distance from particle to grid node as a percentage of grid spacing
        d = (1+particles(1,i)/h) - coord;       
        rho(coord) = rho(coord) + q*d;
        rho(coord+1) = rho(coord+1) + q*(1-d);
    end
    
    % Add background charge
    rho(1:N-1) = rho(1:N-1) + q0*(np/(N-1));
    
    % Periodic BCs at the end points
    rho(N) = rho(N) + rho(1);
    rho(1) = rho(N);
    
    % Calculate the charge density
    rho = rho/h;
    rho(abs(rho)<1e-10) = 0;  % Remove some noise
    
    
    % Solve for potential (Poisson equation) using Gauss-Seidel method and 
    % central difference formula for second derivative
    phi = zeros(1,N);   % Clear the potential vector
    
    SOR = 1.8;  % Successive over relaxation parameter for faster GS method convergence
    for j = 1:20000
        for i = 1:N-1
            if i==1         % When i-1==0
                phi(i) = SOR*0.5*(phi(N-1) + phi(i+1) + (rho(i)/e0)*h^2) + ...
                (1-SOR)*phi(i); % N-1 rather than N, since the BC is periodic, so N==1
            elseif i==N-1   % When i+1==N
                phi(i) = SOR*0.5*(phi(i-1) + phi(1) + (rho(i)/e0)*h^2) + ...
                (1-SOR)*phi(i); 
            else
                phi(i) = SOR*0.5*(phi(i-1) + phi(i+1) + (rho(i)/e0)*h^2) + ...
                (1-SOR)*phi(i); %
            end
        end
        
        % Check for convergence by evaluating residual of Poisson equation on internal points
        if mod(j,25)==0
            resSum = 0;
            for i = 2:N-1
                if i==N-1
                    residual = (rho(i)/e0)+(phi(i-1) - 2*phi(i) + phi(1))/h^2;
                else
                    residual = (rho(i)/e0)+(phi(i-1) - 2*phi(i) + phi(i+1))/h^2;
                end
                resSum = resSum + residual^2;
            end
            if sqrt(resSum/N)<tol
                break
            end
        end
    end
    phi(N) = phi(1); % Periodic BC at end
    
    % Calculate electric field using central difference for first derivative
    for i = 1:N
        if i==1
            E(i) = (phi(N-1)-phi(i+1))/(2*h);
        elseif i==N
            E(i) = (phi(i-1)-phi(2))/(2*h);
        else
            E(i) = (phi(i-1)-phi(i+1))/(2*h);
        end
    end
    
    % Move particles
    for i = 1:np
        % Find electric field at particle position (inverse weighting)
        coord = 1 + floor(particles(1,i)/h);
        d = (1+particles(1,i)/h) - coord;
        E_part = E(coord)*d + E(coord+1)*(1-d);
        
        % Move v back by dt/2, i.e. find v(t-dt/2)
        if t==0
            particles(2,i) = particles(2,i) + 0.5*E_part*qm*dt;
        end
            
        % Calculate v(t+dt/2), use to find x(t+dt) (mistake in Brieda, need an extra step?)
        particles(2,i) = particles(2,i) + E_part*qm*dt;
        particles(1,i) = particles(1,i) + particles(2,i)*dt;
        
        % Periodic BCs to keep the particles in the domain
        if particles(1,i)<0
            particles(1,i) = particles(1,i) + L;
        end
        if particles(1,i)>=L
            particles(1,i) = particles(1,i) - L;
        end
    end
    
    % Plots
    if mod(t,5)==0
        subplot(2,1,1)
        scatter(particles(1,:),particles(2,:),40,colors,'filled','MarkerFaceAlpha',0.5)
        axis([0,2*pi,-pi,pi])
        xlabel('x')
        ylabel('v_x')
        title(sprintf('t = %d',dt*50*floor(t/50)))
        
        subplot(2,1,2)
        plot(1:N,phi,'k',1:N,rho,'g')
        legend('Potential', 'Charge density')
        axis([0,N,-1,1])
        drawnow
        
        % Capture the plot as an image
        frame = getframe(fig);
        im = frame2im(frame);
        [imind,cm] = rgb2ind(im,256);
        
        % Write to the GIF File
        if t == 0
            imwrite(imind,cm,filename,'gif', 'Loopcount',inf);
        else
            imwrite(imind,cm,filename,'gif','WriteMode','append');
        end
        
        % Calculate field quantities
        EK = 0.5*sum(m*particles(2,:).*particles(2,:)); % Kinetic energy
        EP = 0.5*sum(rho.*phi);                         % Electric potential energy
    end
    t = t+1;    % Update time step
end