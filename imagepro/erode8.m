I = imread('M2.tif');
[r,c] =  size(I);
% filter  = [[0 1 0];[1 1 1];[0 1 0]];
padding = zeros(r+2,c+2);
for i=2:r
    for j=2:c
        padding(i,j)=I(i-1,j-1);
    end
end
erodee = zeros(r+2,c+2);
for i=2:r+1
    for j=2:c+1
        if(padding(i-1,j)==1 && padding(i,j-1)==1 && padding(i,j)==1 && padding(i,j+1) && padding(i+1,j))
           erodee(i,j)=1; 
        end
    end
end

for i=1:r+2
    for j=1:c+2
        erodee(i,j)=padding(i,j)-erodee(i,j);
    end
end
imshow(erodee);
