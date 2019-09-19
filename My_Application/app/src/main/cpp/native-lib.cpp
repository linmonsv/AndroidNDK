#include <jni.h>
#include <string>
#include <optional>
#include <thread>
#include <android/log.h>

#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_DATA_BUF_LEN 10240

void * threadFunc(void *arg){
    for(auto i = 0; i < 10000; i ++) {
        __android_log_print(ANDROID_LOG_VERBOSE,"hello","i = %d arg = %s",i,"hehe, thread is ok!");
    }
    return (void *) 0;
}

void testTCP() {
    int sockfd = -1;
    sockaddr_in addr_org;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    __android_log_print(ANDROID_LOG_VERBOSE,"testtcp","sockfd = %d", sockfd);
    addr_org.sin_family = AF_INET;
    addr_org.sin_addr.s_addr = inet_addr("119.123.242.1");
    addr_org.sin_port = htons(7213);
    int ret = connect(sockfd, (struct sockaddr *)&addr_org, sizeof(struct sockaddr));
    __android_log_print(ANDROID_LOG_VERBOSE,"testtcp","connect ret = %d", ret);
    char SendDataBuff[] = "tcp is ok";
    int ulLen = strlen(SendDataBuff);
    send(sockfd, SendDataBuff, ulLen, 0);
}
void * testServer(void *arg){
    int sockServer = -1;
    sockaddr_in addr_org;
    sockServer = socket(AF_INET, SOCK_STREAM, 0);
    __android_log_print(ANDROID_LOG_VERBOSE,"testtcp","sockfd = %d", sockServer);
    int yes = 1;
    setsockopt(sockServer, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    struct sockaddr_in addrServer;
#ifdef WIN32
    addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
#else
    addrServer.sin_addr.s_addr=htonl(INADDR_ANY);
#endif
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(7100);
    int err = bind(sockServer, (struct sockaddr*)&addrServer, sizeof(struct sockaddr));
    __android_log_print(ANDROID_LOG_VERBOSE,"testtcp","bind err = %d", err);
    listen(sockServer, 5);
    struct sockaddr_in addrClient;
    int len = sizeof(struct sockaddr);
    bool isStart = true;
    int length = 0;
    while (isStart) {
        int sockConn = accept(sockServer, (struct sockaddr *) &addrClient, &len);
        if (sockConn < 0) {
            printf("accept() called failed! The error code is: %d\n", sockConn);
        } else {
            printf("The server receive a new client connection!\n");
            char data[8192];
            int length = recv(sockConn, data, sizeof(data) - 1, 0);
            __android_log_print(ANDROID_LOG_VERBOSE,"testtcp","recv length = %d", length);
            send(sockConn, data, length, 0);
            __android_log_print(ANDROID_LOG_VERBOSE,"testtcp","send err = %d", length);
        }
    }
    return (void *) 0;
}
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    pthread_t pthreads;
    pthread_create(&pthreads, NULL, threadFunc, (void *) "zzw");

    testTCP();

    pthread_t pthreads2;
    pthread_create(&pthreads2, NULL, testServer, (void *) "zzw");

    std::optional<std::string> HeHe;
    std::string hello = "Hello World from C++";
    HeHe = "C++ 17 is OK";
    if(HeHe.has_value()) {
        hello = HeHe.value();
    }
    return env->NewStringUTF(hello.c_str());
}
