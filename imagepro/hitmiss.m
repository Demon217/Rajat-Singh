x = imread('M3.tif');
y = double(x);
[r,c]=size(y);
xc=zeros(r,c);
for i=1:r
    for j=1:c
        xc(i,j)=1-y(i,j);
    end
end

%b1 = [[1,1,1];[1,1,1];[1,1,1]];
b2 = [[1,1,1,1,1];[1,0,0,0,1];[1,0,0,0,1];[1,0,0,0,1];[1,1,1,1,1]];

d1=zeros(r,c);

for i=2:r-1
    for j=2:c-1
       flag=0;  
       if(y(i,j)==1)
          if(y(i-1,j-1)==1 &&y(i-1,j)==1&&y(i-1,j+1)==1&&y(i,j-1)==1&&y(i,j+1)==1&&y(i+1,j-1)==1&&y(i+1,j)==1&&y(i+1,j+1)==1) 
           flag=1;
          end 
          if(flag==1)
             d1(i,j)=1; 
          end    
       end    
    end
end

d2=zeros(r,c);
for i=3:r-2
    for j=3:c-2
       flag=0;  
       for l=1:5  
         for m=1:5
          flag=flag+b2(l,m)*y(i-2+l-1,j-2+m-1);  
         end
       end
       if(flag==16)
         d2(i,j)=1;
       end    
    end
end    
res=zeros(r,c);
for i=1:r
    for j=1:c
        if(d2(i,j)==1 && d1(i,j)==1)
            res(i,j)=1;
        end    
    end
end    

subplot(2,1,1),imshow(x);
subplot(2,1,2),imshow(res);