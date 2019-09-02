# Extract pdf pages
pdftk full-pdf.pdf cat 12-15 output outfile_p12-15.pdf

# Download all pdfs on a webpage
wget --no-clobber --convert-links --random-wait -r -p -E -e robots=off -U mozilla http://site/path/

# Find files not matching a pattern in current directory and execute command on them
* **NB: escaped semicolon terminates exec command**
* **NB: remove "-maxdepth 1" to search into subdirectories**

find . -type f ! -name some-regex-pattern-* -maxdepth 1 -exec mv {} some/path/ \;

# Mount flash drive
ls /dev/da*

>> ... /dev/da0s1

mkdir /media/flash
mount_msdosfs /dev/da0s1 /media/flash

ls /media/flash
