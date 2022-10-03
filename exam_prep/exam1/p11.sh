if [ -f "/data/csci2500-proj/" ] 
then 
    rmdir -p /data/csci2500-proj/
fi
mkdir -p /data/csci2500-proj/
cp -a ~/proj/o* /data/csci2500-proj/
chmod -R u=rwx /data/csci2500-proj/
chmod -R g=rw /data/csci2500-proj/
chmod -R o=r /data/csci2500-proj/