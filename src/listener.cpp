//
// Created by wzy on 19-1-4.
#include "ros/ros.h"
#include "fstream"
#include "geometry_msgs/Point.h"


//int name_suffix  = 5;

void pose1Callback(geometry_msgs::Point p1)
{
    //防止动作抖动，设置启动阈值,先存住20行，分成2组比较，,然后判断。
    static int count = 0;

    static double
            p1_buffer[20][3] = {0.0};


    int flag = 0;//用于判断变化change是否过大，作为条件决定是否写入文件,默认flag=0不写入文件。

    if(count < 20)
    {
            p1_buffer[count][0] = p1.x;   p1_buffer[count][1] = p1.y;   p1_buffer[count][2] = p1.z;
            count++;
    }
    else
    {
        double
        buf0_4[3] = {0.0},
        buf5_9[3] = {0.0},
        buf10_14[3] = {0.0},
        buf15_19[3] = {0.0},
        change1[3] = {0.0},
        change2[3] = {0.0};
        int flag_x = 0;
        int flag_y = 0;
        int flag_z = 0;

    for(int i = 0; i <= 4; i++)
    {
        buf0_4[0] += p1_buffer[i][0];  buf0_4[1] += p1_buffer[i][1];  buf0_4[2] += p1_buffer[i][2];
        buf0_4[0] = buf0_4[0] / 5;  buf0_4[1] = buf0_4[1] / 5;  buf0_4[2] = buf0_4[2] / 5;
    }
    for(int i = 5; i <= 9; i++)
    {
        buf5_9[0] += p1_buffer[i][0];  buf5_9[1] += p1_buffer[i][1];  buf5_9[2] += p1_buffer[i][2];
        buf5_9[0] = buf5_9[0] / 5;  buf5_9[1] = buf5_9[1] / 5;  buf5_9[2] = buf5_9[2] /5;
    }
    for(int i = 10; i <= 14; i++)
    {
        buf10_14[0] += p1_buffer[i][0];  buf10_14[1] += p1_buffer[i][1];  buf10_14[2] += p1_buffer[i][2];
        buf10_14[0] = buf10_14[0] / 5;  buf10_14[1] = buf10_14[1] / 5;  buf10_14[2] = buf10_14[2] /5;
    }
    for(int i = 15; i <= 19; i++)
    {
        buf15_19[0] += p1_buffer[i][0];  buf15_19[1] += p1_buffer[i][1];  buf15_19[1] += p1_buffer[i][2];
        buf15_19[0] = buf15_19[0] / 5;  buf15_19[1] = buf15_19[1] / 5;  buf15_19[2] = buf15_19[2] / 5;
    }
        //计算2组变化值
    change1[0] = buf0_4[0] - buf10_14[0];   change2[0] = buf5_9[0] - buf15_19[0];
    change1[1] = buf0_4[1] - buf10_14[1];   change2[1] = buf5_9[1] - buf15_19[1];
    change1[2] = buf0_4[2] - buf10_14[2];   change2[2] = buf5_9[2] - buf15_19[2];


    if((change1[0]>10 || change1[0]<(-10)) && (change2[0]>10 || change2[0]<(-10)))
        flag_x = 1;
    if((change1[1]>10 || change1[1]<(-10)) && (change2[1]>10 || change2[1]<(-10)))
        flag_y = 1;
    if((change1[2]>10 || change1[2]<(-10)) && (change2[2]>10 || change2[2]<(-10)))
        flag_z = 1;

    if(flag_x || flag_y || flag_z)
        flag = 1;

    count = 0;
    }

    if(flag)
    {
        std::ofstream file_p_LH;
        uint64_t nsec = ros::Time::now().toNSec();
        std::ostringstream oss;

        std::string filename = "record_p_LH";
        std::string file = "/home/wzy/Record/" + filename + ".txt";

        file_p_LH.open(file.c_str(), std::ios::app);

        for(int i = 0; i < 20;i++)
        file_p_LH << p1_buffer[i][0] << "       " << p1_buffer[i][1] << "       " << p1_buffer[i][2] << "\n";

        file_p_LH.close();
    }
}

void pose2Callback(geometry_msgs::Point p2)
{
    std::ofstream file_p_LE;
    uint64_t nsec = ros::Time::now().toNSec();
    std::ostringstream oss;

    std::string filename = "record_p_LE";
    std::string file = "/home/wzy/Record/" + filename + ".txt";
    file_p_LE.open(file.c_str(), std::ios::app);

    file_p_LE << p2.x<<"  "<<p2.y<<"  "<<p2.z<<"\n";

    file_p_LE.close();
}
void pose3Callback(geometry_msgs::Point p3)
{
    std::ofstream file_p_LS;
    uint64_t nsec = ros::Time::now().toNSec();
    std::ostringstream oss;

    std::string filename = "record_p_LS";
    std::string file = "/home/wzy/Record/" + filename + ".txt";
    file_p_LS.open(file.c_str(), std::ios::app);

    file_p_LS << p3.x<<"  "<<p3.y<<"  "<<p3.z<<"\n";

    file_p_LS.close();
}
void pose4Callback(geometry_msgs::Point p4)
{
    std::ofstream file_p_LP;
    uint64_t nsec = ros::Time::now().toNSec();
    std::ostringstream oss;

    std::string filename = "record_p_LP";
    std::string file = "/home/wzy/Record/" + filename + ".txt";
    file_p_LP.open(file.c_str(), std::ios::app);

    file_p_LP << p4.x<<"  "<<p4.y<<"  "<<p4.z<<"\n";

    file_p_LP.close();
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "listener");
    ros::NodeHandle nh_;
    ros::Subscriber sub1 = nh_.subscribe("pose1",1000,pose1Callback);
    ros::Subscriber sub2 = nh_.subscribe("pose2",1000,pose2Callback);
    ros::Subscriber sub3 = nh_.subscribe("pose3",1000,pose3Callback);
    ros::Subscriber sub4 = nh_.subscribe("pose4",1000,pose4Callback);




    ros::spin();
return 0;
}
