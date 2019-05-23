x = [[1,1,1,1,1,1,1];
    [1,1,1,1,1,1,1];
    [1,0,0,0,0,0,1];
    [1,0,0,0,0,0,1];
    [1,1,1,1,1,1,1];
    [1,1,1,0,0,0,1];
    [1,1,1,1,1,0,0]];
[r,c]=size(x);
y = zeros(r,c);

xc = zeros(r+1,c+1);

for i=1:r
    for j=1:c
        
    end
end

for i=1:r
    for j=1:c
        y(i,j)=1-x(i,j);
    end
end    
imshow(y);