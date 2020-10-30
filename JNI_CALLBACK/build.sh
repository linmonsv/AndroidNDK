g++ main.cpp libHello.cpp -o hello
g++ libHello.cpp -fPIC -shared -o libHello.so
g++ main.cpp -L. -lHello -o hello_so

echo $LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
echo $LD_LIBRARY_PATH

#sudo apt install openjdk-8-jdk
