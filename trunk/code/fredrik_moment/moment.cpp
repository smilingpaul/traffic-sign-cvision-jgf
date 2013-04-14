#include <opencv2/opencv.hpp>
#include <cmath>

#include "moment.h"

using namespace cv;


int get_moment(const Mat& src, int p, int q){
	long int moment = 0;
	for(int i = 0; i < src.rows; i++){
		for(int j = 0; j < src.cols; j++){
			if(src.at<char>(i,j) != 0){
				moment += pow(i,p)*pow(j,q);
			}
		}
	}
	return moment;
}

double get_central_moment(const Mat& src, int p, int q){
	double moment = 0;
	
	int m_00 = get_moment(src, 0, 0);
	int m_10 = get_moment(src, 1, 0);
	int m_01 = get_moment(src, 0, 1);
	double center_of_mass_x = ((double)m_10)/m_00;
	double center_of_mass_y = ((double)m_01)/m_00;

	for(int i = 0; i < src.rows; i++){
		for(int j = 0; j < src.cols; j++){
			if(src.at<char>(i,j) != 0){
				moment += pow(i-center_of_mass_x,p)*pow(j-center_of_mass_y,q);
			}
		}
	}

	return moment;
}

void get_covariance_eig_val(const Mat& src, double *eig_val_1, double *eig_val_2){
	
	double mu_00 = get_central_moment(src, 0,0);
	double mu_11 = get_central_moment(src, 1,1);
	double mu_20 = get_central_moment(src, 2,0);
	double mu_02 = get_central_moment(src, 0,2);

	double mu_20_bar = mu_20/mu_00;
	double mu_02_bar = mu_02/mu_00;
	double mu_11_bar = mu_11/mu_00;

	double first_term_of_eig_func = (mu_20_bar+mu_02_bar)/2;
	double second_term_of_eig_func = sqrt(pow((mu_20_bar - mu_02_bar)/2,2)+pow(mu_11_bar,2));
	
	*eig_val_1 = first_term_of_eig_func + second_term_of_eig_func;
	*eig_val_2 = first_term_of_eig_func - second_term_of_eig_func;
}

