# Extract pdf pages
pdftk full-pdf.pdf cat 12-15 output outfile_p12-15.pdf

# Download all pdfs on a webpage
wget --no-clobber --convert-links --random-wait -r -p -E -e robots=off -U mozilla http://site/path/
