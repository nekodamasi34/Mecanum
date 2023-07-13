#include "mbed.h"
#include "math.h"

#include "Movement.h"


Movement::Movement()
{}

void Movement::up_limit_balance(double duty[], double units_num, double limit)
{
	double max_duty = 0;
	// max_dutyにduty[i]の最大値を格納
	for(int i = 0; i < units_num; i++){
		if(fabs(duty[i]) > max_duty)
	    	max_duty = fabs(duty[i]);
	}

	// 各車輪の比率を保ちながらduty[i]の最大値をlimitに引き上げ
	if( max_duty != 0 && ( max_duty < limit ) ){
	   	for(int i = 0; i < units_num; i++)
	   		duty[i] *= limit / max_duty;
	}
}

void Movement::down_limit_balance(double duty[], double units_num, double limit)
{
    // 各車輪の比率を保ちながらduty[i]を上限以下に引き下げ
    for(int i = 0; i < units_num; i ++){
        if(fabs(duty[i]) > limit){
            double inv = fabs(duty[i]);
            for(int j = 0; j < units_num; j ++)
                duty[j] *= limit / inv;
        }
    }
}

void Movement::move(Eigen::Vector3d move_vector)
{
	move(move_vector(X), move_vector(Y), move_vector(Yaw));
}