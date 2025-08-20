(ii) How do you create a new directory in Linux using the mkdir 
command in Linux?
mkdir <directory_name>

(iii) How do you navigate to the parent directory using the cd command 
in Linux? 
cd <directory_name>
Example: cd /home/user/documents

(iv) How do you change the permissions of a file or directory using the 
chmod command in Linux?
chmod <permissions> <file_or_directory>
Example: chmod 755 myfile.txt
🔎 Breakdown of 755:
7 (owner) → rwx → read, write, execute
5 (group) → r-x → read, execute
5 (others) → r-x → read, execute
So after running it:
The owner can read, write, and execute the file.
The group and others can only read and execute it (not write).