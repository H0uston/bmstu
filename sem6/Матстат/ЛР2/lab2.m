function lab2()

    X = [-14.34,-16.97,-14.09,-14.74,-16.69,-13.85,-15.55,-14.62,-13.30,-15.52,-14.75,-16.51,-17.15,-16.87,-15.06,-13.60,-14.48,-14.71,-14.17,-13.88,-14.55,-15.37,-14.81,-16.05,-17.06,-15.86,-15.12,-15.98,-14.16,-15.81,-15.06,-16.19,-16.22,-16.19,-14.87,-15.62,-15.86,-15.25,-16.34,-14.44,-14.72,-15.17,-15.24,-14.44,-15.93,-14.87,-16.53,-15.76,-15.12,-12.91,-16.06,-16.06,-14.89,-15.57,-13.59,-16.84,-13.88,-14.33,-15.45,-16.58,-16.05,-14.34,-13.55,-16.78,-14.15,-14.28,-14.40,-13.98,-16.23,-15.35,-14.77,-15.61,-15.59,-15.64,-14.76,-17.18,-15.13,-15.01,-14.21,-13.91,-16.55,-15.44,-14.03,-16.44,-15.57,-15.07,-16.28,-16.30,-15.74,-14.03,-14.85,-15.73,-15.81,-14.42,-14.14,-15.14,-15.49,-16.42,-14.22,-14.20,-17.17,-15.82,-14.96,-14.75,-14.98,-13.64,-14.00,-17.29,-14.51,-16.18,-15.70,-15.07,-14.28,-14.55,-13.85,-15.36,-15.74,-14.61,-16.32,-15.34];
    % X = [11.89,9.60,9.29,10.06,9.50,8.93,9.58,6.81,8.69,9.62,9.01,10.59,10.50,11.53,9.94,8.84,8.91,6.90,9.76,7.09,11.29,11.25,10.84,10.76,7.42,8.49,10.10,8.79,11.87,8.77,9.43,12.41,9.75,8.53,9.72,9.45,7.20,9.23,8.93,9.15,10.19,9.57,11.09,9.97,8.81,10.73,9.57,8.53,9.21,10.08,9.10,11.03,10.10,9.47,9.72,9.60,8.21,7.78,10.21,8.99,9.14,8.60,9.14,10.95,9.33,9.98,9.09,10.35,8.61,9.35,10.04,7.85,9.64,9.99,9.65,10.89,9.08,8.60,7.56,9.27,10.33,10.09,8.51,9.86,9.24,9.63,8.67,8.85,11.57,9.85,9.27,9.69,10.90,8.84,11.10,8.19,9.26,9.93,10.15,8.42,9.36,9.93,9.11,9.07,7.21,8.22,9.08,8.88,8.71,9.93,12.04,10.41,10.80,7.17,9.00,9.46,10.42,10.43,8.38,9.01];
    % X = [1.52,1.26,2.17,1.75,-0.19,2.24,2.76,1.52,1.89,3.10,2.61,1.18,1.83,1.85,3.39,2.31,2.99,1.61,2.57,1.81,1.73,1.89,-0.00,2.27,1.61,2.57,2.54,1.67,1.49,0.12,-0.04,1.36,2.04,2.04,-0.05,0.67,1.32,0.78,0.89,2.73,1.51,1.48,1.67,2.18,1.70,4.20,1.81,2.66,1.72,0.77,3.16,1.86,3.66,4.30,0.98,3.00,0.99,1.72,2.71,2.47,2.56,1.99,0.23,0.66,2.47,2.71,2.28,2.59,3.30,2.08,0.90,0.49,2.38,0.71,0.10,1.50,0.21,0.44,3.94,1.50,1.70,-0.73,1.76,2.71,1.95,-0.71,1.32,3.95,2.64,-0.04,3.24,1.67,2.31,0.18,0.79,3.26,3.44,2.64,0.89,2.47,4.02,2.12,0.61,2.59,1.44,1.82,2.94,3.03,1.97,2.30,0.80,0.52,1.21,2.13,2.82,1.56,2.84,3.54,0.86,0.42];
    N = 1:length(X); 
    
    gamma = 0.9;
    alpha = (1 - gamma)/2;

    mu = math_expectation(X);
    
    s_sqr = variance(X); 

    muArray = expectationArray(X, N);
    varArray = varianceArray(X, N);
 
    figure
    plot([N(1), N(end)], [mu, mu], 'black');
    hold on;
    plot(N, muArray, 'g');
    
    Ml = muArray - sqrt(varArray./N).*tinv(1 - alpha, N - 1);
    plot(N, Ml, 'b');
    
    Mh = muArray + sqrt(varArray./N).*tinv(1 - alpha, N - 1);
    plot(N, Mh, 'r');
    grid on;
    hold off;

    fprintf('mu = %.2f\n', mu); 
    fprintf('S^2 = %.2f\n\n', s_sqr);
    fprintf('mu_low = %.2f\n', Ml(end));
    fprintf('mu_high = %.2f\n', Mh(end));

    
    figure
    plot([N(1), N(end)], [s_sqr, s_sqr], 'black');
    hold on;
    plot(N, varArray, 'g');
    
    Sl = varArray.*(N - 1)./chi2inv(1 - alpha, N - 1);
    plot(N, Sl, 'b');
    
    Sh = varArray.*(N - 1)./chi2inv(alpha, N - 1);
    plot(N, Sh, 'r');
    grid on;
    hold off;
    fprintf('sigma^2_low = %.2f\n', Sl(end));
    fprintf('sigma^2_high = %.2f\n', Sh(end));
end

function mu = math_expectation(X)
    mu = sum(X) / length(X);
end

function s_sqr = variance(X)
    s_sqr = var(X);
end

function muArray = expectationArray(X, N)
    muArray = [];
    for i = N
        muArray = [muArray, mean(X(1:i))];
    end
end

function varArray = varianceArray(X, N)
    varArray = [];
    for i = N
        varArray = [varArray, var(X(1:i))];
    end
end