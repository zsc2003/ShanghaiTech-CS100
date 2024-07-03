mv foo.c submission.zip
mkdir submission
unzip -qq submission.zip -d submission
cd submission
echo "Got submissions:"
ls .
if [ ! -f pacman.c ]; then
    echo -e "\e[1;31mWhere is your pacman.c?\033[0m"
    exit 42
fi
for file in *; do
    if [[ $file = *.c ]] || [[ $file = *.h ]]; then
        echo "================================================================================"
        echo "$file":
        echo "-------------"
        pygmentize $file
        echo
    fi
done
cd ..
touch foo