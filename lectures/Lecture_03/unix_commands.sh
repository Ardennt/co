#/bin/bash

# what is path of my home directory?
echo $HOME

# can also use
echo ~

# list absolute path of current directory
pwd

# list contents of current directory
ls

# list them with details
ls -l

# list all files (even hidden ones -- they start with a '.')
ls -la

# list sorted by size
ls -la --sort=size

# with human-readable sizes
ls -lah --sort=size

# create directory
mkdir my_mega_fun_dir

# change permissions on that directory -- only we can access it
chmod 700 my_mega_fun_dir

# change it back -- we can do anything, everyone else can read/access
# Note: directories need executable permissions in order to be accessed
chmod a+rx my_mega_fun_dir

# move to that directory
cd my_mega_fun_dir

# create files 'woo' and 'woo2' in parent directory
touch ../woo
touch ../woo2

# copy woo to this directory
copy ../woo .

# or move it (will remove the original version)
mv ../woo .

# copy all files from parent directory
cp ../* .

# create a new file by combining out two woos
cat woo woo2 > meow

# remove woos from this directory
rm woo woo2 

# move back to parent directory
cd ..

# remove our new directory (-r signifies recursive removal)
rm -r my_mega_fun_dir/

# Quit messing around and go home
rm woo2
cd ~
