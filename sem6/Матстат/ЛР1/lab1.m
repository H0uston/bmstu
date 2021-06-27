function lab1()    
    X = [-14.34,-16.97,-14.09,-14.74,-16.69,-13.85,-15.55,-14.62,-13.30,-15.52,-14.75,-16.51,-17.15,-16.87,-15.06,-13.60,-14.48,-14.71,-14.17,-13.88,-14.55,-15.37,-14.81,-16.05,-17.06,-15.86,-15.12,-15.98,-14.16,-15.81,-15.06,-16.19,-16.22,-16.19,-14.87,-15.62,-15.86,-15.25,-16.34,-14.44,-14.72,-15.17,-15.24,-14.44,-15.93,-14.87,-16.53,-15.76,-15.12,-12.91,-16.06,-16.06,-14.89,-15.57,-13.59,-16.84,-13.88,-14.33,-15.45,-16.58,-16.05,-14.34,-13.55,-16.78,-14.15,-14.28,-14.40,-13.98,-16.23,-15.35,-14.77,-15.61,-15.59,-15.64,-14.76,-17.18,-15.13,-15.01,-14.21,-13.91,-16.55,-15.44,-14.03,-16.44,-15.57,-15.07,-16.28,-16.30,-15.74,-14.03,-14.85,-15.73,-15.81,-14.42,-14.14,-15.14,-15.49,-16.42,-14.22,-14.20,-17.17,-15.82,-14.96,-14.75,-14.98,-13.64,-14.00,-17.29,-14.51,-16.18,-15.70,-15.07,-14.28,-14.55,-13.85,-15.36,-15.74,-14.61,-16.32,-15.34];

    X = sort(X);
    
    minX = X(1);
    fprintf('Mmin = %s\n', num2str(minX));

    maxX = X(end);
    fprintf('Mmax = %s\n', num2str(maxX));

    R = maxX - minX;
    fprintf('R = %s\n', num2str(R));

    mx = expectation(X);
    fprintf('MX = %s\n', num2str(mx));

    sigma = dispersion(X);
    fprintf('DX = %s\n', num2str(sigma));

    s = unbiasedDispersion(X);
    fprintf('nDX: %s\n', num2str(s));

    m = subintervals(length(X));
    fprintf('m = %s\n ', num2str(m));
    
    intervals(X, m);
    hold on;
    f(X, mx, s, m);
    
    figure;
    empiricF(X);
    hold on;
    F(X, mx, s, m);
        
end

function m = subintervals(size)
    m = floor(log2(size) + 2);
end

function mu = expectation(X)
    n   = length(X);
    sum = 0;

    for i = 1:n
        sum = sum + X(i);
    end
    
    mu = sum / n;
end

function sigmaSqr = dispersion(X)
    n   = length(X);
    sum = 0;

    for i = 1:n
        sum = sum + (X(i))^2;
    end
    
    mu  = expectation(X);
    
    sigmaSqr = sum / n - mu^2;
end

function sSqr = unbiasedDispersion(X)
    sigmaSqr = dispersion(X);
    n        = length(X); 

    sSqr = n / (n - 1) * sigmaSqr;
end

function intervals(X, m)
    count = zeros(1, m+2);  
    delta = (X(end) - X(1)) / m;
    
    J = X(1):delta:X(end);
    fprintf('%d\n', X(end));
    J(length(J)+1) = 20;
    
    j = 1;
    n = length(X);
    
    for i = 1:n      
        if (j ~= m)
            if ((not (X(i) >= J(j) && X(i) < J(j+1))))
                j = j + 1;
                fprintf('[%.2f;%.2f)\t', J(j-1), J(j));
            end
        end
        count(j) = count(j) + 1;
    end
    fprintf('[%2.2f;%2.2f]\n', J(m), J(m + 1));
    
    Xbuf = count(1:m+2);
    for i = 1:m+2
        Xbuf(i) = count(i) / (n*delta); 
    end
   
    stairs(J, Xbuf), grid;
end

function f(X, MX, DX, m)
    R = X(end) - X(1);
    delta = R/m;
    Sigma = sqrt(DX);
    
    Xn = (MX - R): delta/50 :(MX + R);
    Xn(length(Xn)+1) = 20;
    Y = normpdf(Xn, MX, Sigma);
    
    plot(Xn, Y);
end

function F(X, MX, DX, m)
    R = X(end) - X(1);
    delta = R/m;
    
    Xn = (MX - R): delta :(MX + R);
    
    Y = 1/2 * (1 + erf((Xn - MX) / sqrt(2*DX))); 
    
    
    plot(Xn, Y, 'r');
end

function empiricF(X)  
    [yy, xx] = ecdf(X);
    yy(length(yy)+1) = 1;
    xx(length(xx)+1) = 20;
    
    stairs(xx, yy);
end