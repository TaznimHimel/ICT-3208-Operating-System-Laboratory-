(ii) How do you create a new user in Linux? 
sudo adduser <username>
Example: sudo adduser meaw

(iii) How do you delete a user in Linux? 
sudo deluser <username>

(iv) How do you change the password of a user in Linux? 
sudo passwd <username>
Example: sudo passwd john

(v) How do you add a user to a group in Linux? 
sudo usermod -aG <groupname> <username>
Example: sudo usermod -aG developers john

(vi) How do you remove a user from a group in Linux?
sudo gpasswd -d <username> <groupname>
Example: sudo gpasswd -d john developers

(v) How do you create a new group in Linux?
sudo addgroup <groupname>
Example: sudo addgroup developers

(vi) How do you delete a group in Linux?
sudo delgroup <groupname>
Example: sudo delgroup developers

(vii) How do you display the members of a group in Linux?
getent group <groupname>
Example: getent group developers

# 3_cmd.sh
# This script contains commands for user and group management in Linux.
# Usage: Source this script to use the commands.
# Example: source 3_cmd.sh