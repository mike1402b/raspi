#start ssh Agent
eval $(ssh-agent -s)
#add ssh key, so don't have to enter passphrase everytime
ssh-add ~/.ssh/id_rsa
