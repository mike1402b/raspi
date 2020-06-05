git config --global user.email "mike1402@gmx.at"
git config --global user.name "mike1402b"
git config --local user.email "mike1402@gmx.at"
git config --local user.name "mike1402b"

#create rsa key pair for github
ssh-keygen -t rsa -b 4096 -C "mike1402@gmx.at"

#display public key for adding to github
cat ~/.ssh/id_rsa.pub
