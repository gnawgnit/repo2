#!/bin/bash
#autor gnawgnit
git  clone https://github.com/gnawgnit/repo4.git
git  remote add origin https://github.com/gnawgnit/repo4.git

cd repo4
touch connect.txt
echo "按:q进入编辑区" >> connect.txt
clear
for ((i=0;i<=10;i=0))
do
git  pull origin master
vim -R connect.txt
:> connect.bak
vim connect.bak
date >> connect.txt
cat connect.bak >> connect.txt
git  pull origin master
clear
cat connect.txt

git add connect.txt
git commit -m "none"
git  pull origin master
git push -u origin master
done
