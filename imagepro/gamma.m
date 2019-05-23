x = imread('E1.tif');
x1 = double(x);
[r,c]=size(x1);
g = 2;
y = 1;
for i = 1:r
    for j = 1:c
        x1(i,j)=(y*(x1(i,j)^g))/255.0;
    end
end

subplot(2,1,1),imshow(x);
title('old');
subplot(2,1,2),imshow(uint8(x1));
title('new');