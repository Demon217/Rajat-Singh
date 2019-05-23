x = imread('E1.tif');
y = double(x);
values = zeros(256,1);
[r,c]=size(y);
for i=1:r
    for j=1:c
        values(y(i,j)+1)=values(y(i,j)+1)+1; 
    end
end    

for i=1:255
    for j=1:255
        if values(j) > values(j+1)
            l=values(j);
            values(j)=values(j+1);
            values(j+1)=l;
        end
    end
end


    