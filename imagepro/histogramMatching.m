x = imread('E3-2.tif');
y = imread('E3-3.tif');
x1 = double(x);
y1 = double(y);
[r,c] = size(x1); 
l = zeros(256,1);
m = zeros(256,1);
for i = 1:r
    for j = 1:c
        l(x1(i,j)+1)=l(x1(i,j)+1)+1;
    end
end
for i = 1:r
    for j = 1:c
        m(y1(i,j)+1)=m(y1(i,j)+1)+1;
    end
end

for i= 2:256
    l(i)=l(i)+l(i-1);
    m(i)=m(i)+m(i-1);
end

for i = 1:256
    l(i)=l(i)/(r*c);
    m(i)=m(i)/(r*c);
end

for i = 1:256
    l(i)=l(i)*255;
    m(i)=m(i)*255;
end

newmap = zeros(256,1);
i=1;
j=1;

while (j < 257)
    while (m(j) >= l(i))   
       newmap(i)=j-1;     
       i=i+1; 
       if(i==257)
           break;
       end    
    end
    if(i==257)
           break;
       end    
    j=j+1;
end

for i = 1:r
    for j = 1:c
        y1(i,j)=newmap(y1(i,j)+1);
    end
end

subplot(1,2,1),imshow(y);
title('before');
subplot(1,2,2),imshow(uint8(y1));
title('after');

