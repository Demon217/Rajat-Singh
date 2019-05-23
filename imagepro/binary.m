function [arr] = binary(val)
arr = zeros(1,8);
i=0;
val=uint(val);
while val > 0
   arr(1,8-i)=mod(val,2); 
   val=val/2; 
   i=i+1;
   if(i==8)
       break;
   end    
end    