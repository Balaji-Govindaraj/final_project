c='C:\Users\HP8\Documents\MATLAB\fingerprint-master\1.jpg';
pro(c,'101_6.tif');

com= database('root','root','','com.mysql.jdbc.Driver','jdbc:mysql://localhost/');


sqlquery=sprintf('select array from root where id=%d',8);
results = fetch(com,sqlquery);
a=results(1);
b=sprintf('%s',a{:});
x=imread(b);
count=0;
disp('Hari the output');
disp(x);
compare_img=imread('1.jpg');
disp(compare_img);
in=0;
for i=1:1:3
    for j=1:1:50
        in=in+1;
       if x(i,j)==compare_img(i,j)
           count=count+1;
       end
    end
end
disp(in);
disp(count);
%imread(a);


