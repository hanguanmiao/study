## grpc编译  
```
protoc --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` helloworld.proto
protoc --cpp_out=. helloworld.proto
g++ -o server helloworld.pb.cc helloworld.grpc.pb.cc server.cc -L/usr/local/lib `pkg-config --cflags protobuf grpc` -std=c++11 `pkg-config --libs protobuf grpc++ grpc` -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl
```
