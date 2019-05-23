I = imread('M1-1.tif');
[r,c] = size(I);
filter = [[0 1 0]; [1 1 1]; [0 1 0]];
padding = zeros(r+2,c+2);
for i=2:r
    for j=2:c
        padding(i,j)=I(i-1,j-1);
    end
end
dilate = zeros(r+2,c+2);
flag = 0;
z =0;
for i=2:r+1
    for j=2:c+1
        flag=0;
        a=1;
        for k=i-1:i+1
            b=1;
            for l=j-1:j+1
                if(uint8(filter(a,b)*padding(k,l))==1) 
                    flag  = 1;
                    break;
                end
            b=b+1;    
            end
            if(flag==1)
                break;
            end
            a=a+1;
        end
       if(flag==1)
            X = 1;
            for k=i-1:i+1
                Y = 1;
                for l=j-1:j+1
                    if(filter(X,Y)==1)
                        dilate(k,l)=1;
                        z=z+1;
                    end
                    Y=Y+1;
                end
                X=X+1;
            end 
       end
    end
end
imshow(dilate);