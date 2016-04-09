echo
echo "Building both App and Tests from scratch "
echo
./buildTest.sh
echo
echo "Running Tests before building applications "
echo
./Tests
echo

while true; do
    read -p "Do you wish to continue building app?" yn
    case $yn in
        [YyOo]* ) ./buildReal.sh; break;;
        [Nn]* ) exit;;
        * ) echo "Please answer yes or no.";;
    esac
done


