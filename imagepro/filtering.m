x = imread('E5.tif');
x1 = double(x);
z = ones(15,15);
[r,c]=size(x1);
newim = zeros(r+14,c+14);
for i=8:r+7
    for j=8:c+7
        newim(i,j)=x1(i-7,j-7);
    end
end

for i=1:r
   for j=1:c
        an = 0;
        for l = 1:15
            for m = 1:15
                an=an+(newim(i+l-1,j+m-1)*z(l,m)); 
            end
        end
    an=an/255;
    x1(i,j)=an;
    end        
end
subplot(1,2,1),imshow(x);
title('before');
subplot(1,2,2),imshow(uint8(x1));
title('after');
