prompt='0 for exit/1 to continue:';
%i=1;
%x=input(prompt);
for i=1:3000
x=input(prompt);
if x==0
    exit(0);
end
    
c='C:\Users\HP8\Documents\MATLAB\fingerprint-master\image_store\';
v=strcat(c,num2str(i));
y=strcat(v,'.jpg');
pro(y);
com= database('root','root','','com.mysql.jdbc.Driver','jdbc:mysql://localhost/');
%x = com.Handle
a = isconnection(com);
display(a);
%
ch1=zeros(1,10);
colnames={'array'};
datas={y};%,ch1(3),ch1(4),ch1(5),ch1(6),ch1(7),ch1(8),ch1(9),ch1(10),ch1(11),ch1(12),ch1(13),ch1(14),ch1(15),ch1(16),ch1(17),ch1(18),ch1(19),ch1(20),ch1(21),ch1(22),ch1(23),ch1(24),ch1(25),ch1(26),ch1(27),ch1(28),ch1(29),ch1(30),ch1(31),ch1(32),ch1(33),ch1(34),ch1(35),ch1(36),ch1(37)};
insert(com,'root',colnames,datas);
%sqlquery='select * from root';
%results = fetch(com,sqlquery);
%display(results);
%disp(y)
%}
end;
