#pragma once
#include  <opencv2/opencv.hpp>
using  namespace  cv;

#include  <iostream>
using  namespace  std;


//方向 ，与x轴正方向的夹角，与y轴正方向的夹角. 
//应当注意，这里的数值不能是任意数值，应当受到一个基本约束:其和不小于90度 不超过180度
//约束：angle_to_x + angle_to_y >= 90  &&  angle_to_x + angle_to_y <=  90   
typedef  struct direction
{
	double angle_to_x;
	double angle_to_y;
}tp_derection;


typedef  struct rotation
{
	tp_derection  dt;
	double angle_alpha;   //  angle_alpha  是任意数值，但是一般来说应用中应当比零大
}tp_rotation;



class SphericalEquidistantProjectionModel
{
public:
	SphericalEquidistantProjectionModel();
	~SphericalEquidistantProjectionModel();

private:
	const double   radius = 1.0;  //这个是本类的基本设定，球体半径为1.0.   
public:
	double  angle_of_fisheye_camera; //default   CV_PI  

public:
	//这里是讲的球面上的彼此对应，与其它无关。
	//球面点直接落下
	cv::Point2d  fall__sphereToDescartes(tp_derection   drt,   int   posi)
	{
		double x = cos(  drt.angle_to_x );
		double y = cos(  drt.angle_to_y);
		return cv::Point2d(  x,  y  );
	}

	//球面点直接落下
	//这里的x,y是有正有负的
	//这里应当知道，图像坐标系建立在圆心为原点处
	tp_derection  fall__descartesToSphere(cv::Point2d    pd ,  int  positive_z  )
	{
		double angle_to_x = 0;
		double angle_to_y = 0;

		angle_to_x = acos(pd.x);
		angle_to_y = acos(pd.y);

		tp_derection  dr;
		dr.angle_to_x = angle_to_x;
		dr.angle_to_y = angle_to_y;
		return dr;
	}



	double  get_gama(tp_derection   drt, int  positive_z)
	{

		double x = cos(drt.angle_to_x);
		double y = cos(drt.angle_to_y);
		double  r_xy_plane = sqrt(pow(x, 2) + pow(y, 2));
		double angle_x_plane = acos(x / r_xy_plane);
		double angle_y_plane = acos(x / r_xy_plane);


		double  h_p2 = sqrt(1.0 - pow(r_xy_plane, 2));
		double  gama = acos(h_p2);
		return gama;
	}




	//这里是讲的球面上的彼此对应，与其它无关。
	// equiDistance
	cv::Point2d  equiDistance__sphere_2_Descartes (tp_derection   drt,  int  positive_z )
	{
		double x = cos(drt.angle_to_x);
		double y = cos(drt.angle_to_y);
		double  r_xy_plane = sqrt(pow(x, 2) + pow(y, 2)); 
		double angle_x_plane = acos(  x/ r_xy_plane   );
		double angle_y_plane = acos(x / r_xy_plane);


		double  h_p2 = sqrt(  1.0 - pow(r_xy_plane , 2)  );
		double  gama = acos(h_p2);
		double  lenth_sphere = gama* radius;
		double  persent_sphere = lenth_sphere/(radius* CV_PI/2.0 );

		double  persent_descart = persent_sphere;
		double lenth_descart = persent_descart* radius;
		double x_update = lenth_descart * cos(angle_x_plane);
		double y_update = lenth_descart * cos(angle_y_plane);
		return cv::Point2d(x_update, y_update);
	}


	//这里是讲的球面上的彼此对应，与其它无关。
	// equiDistance
	tp_derection  equiDistance__descartes_2_Sphere (cv::Point2d    pd, int  positive_z)
	{
		tp_derection  dr;
		double angle_to_x;
		double angle_to_y;

		//angle_to_x = acos(pd.x);
		//angle_to_y = acos(pd.y);
		//dr.angle_to_x = angle_to_x;
		//dr.angle_to_y = angle_to_y;
		//return dr;


		if (1   )
		{
			// 坐标平面xoy上的计算
			double  r_xy_plane = sqrt(pow(pd.x, 2) + pow(pd.y, 2));
			double angle_x_plane = acos(pd.x / r_xy_plane);  //平面内的夹角
			double angle_y_plane = acos(pd.y / r_xy_plane);
			double  lenth_descart = r_xy_plane;//  sqrt(1.0 - pow(r_xy_plane, 2));
			double  percent_descart = lenth_descart / 1.0;

			// 球体表面的计算
			double  percent_sphere = percent_descart;
			double  lenth_sphere = percent_descart* radius* CV_PI / 2.0;
			double  gama = lenth_sphere / radius;
			double  h_sphere = radius* cos(gama);  // 竖直方向上的投影

			double  lenth_xy_plane = sqrt(1.0 - pow(h_sphere, 2));

			double  x_update = lenth_xy_plane *cos(angle_x_plane);
			double  y_update = lenth_xy_plane *cos(angle_y_plane);

			angle_to_x = acos(x_update);
			angle_to_y = acos(y_update);


			dr.angle_to_x = angle_to_x;
			dr.angle_to_y = angle_to_y;
			return dr;
		}

	}


	//这里是讲的球面到目标图像的平面上的映射，依然按照单位1.0作为基本度量
	cv::Point2d  fall__sphere_2_Descartes__ImagePlane(tp_derection   drt, int  positive_z, double  distance, double  f)
	{
		double x = cos(drt.angle_to_x);
		double y = cos(drt.angle_to_y);
		double  r_xy_plane = sqrt(pow(x, 2.0) + pow(y, 2.0));
		double angle_x_plane;// = acos(x / r_xy_plane);
		double angle_y_plane;// = acos(y / r_xy_plane);
		if (r_xy_plane == 0)
		{
			angle_x_plane = CV_PI / 2.0;
			angle_y_plane = CV_PI / 2.0;
		}
		else
		{
			angle_x_plane = acos(x / r_xy_plane);
			angle_y_plane = acos(y / r_xy_plane);
		}

		double  h_p2 = sqrt(1.0 - pow(r_xy_plane, 2.0));
		if (h_p2 <= 1.0e-99)
		{
			h_p2 = 1.0e-99;
		}

		//   double h_l = f*  () / ();

		double  lamda = f / (f + h_p2)* (f + distance) / f;//   (distance - h_p2) / h_p2;
		if (f == 0)
			lamda = 1.0;

		double  x_normal;
		double  y_normal;

		//x_normal = cos(angle_x_plane)*  lamda;
		//y_normal = cos(angle_y_plane)*  lamda;

		x_normal = x*  lamda;
		y_normal = y*  lamda;

		//return   cv::Point2d( x , y );


		return   cv::Point2d(x_normal, y_normal);
	}

	//这里是讲的球面到目标图像的平面上的映射，依然按照单位1.0作为基本度量
	// 像球面到透视图像平面    把Z轴作为展开的主光轴
	cv::Point2d  equiDistance__sphere_2_Descartes__ImagePlane(tp_derection   drt, int  positive_z,  double  distance,double  f  )
	{
		double x = cos(drt.angle_to_x);
		double y = cos(drt.angle_to_y);
		double  r_xy_plane = sqrt(pow(x, 2.0) + pow(y, 2.0));
		double angle_x_plane;// = acos(x / r_xy_plane);
		double angle_y_plane;// = acos(y / r_xy_plane);
		if (r_xy_plane == 0)
		{
			angle_x_plane = CV_PI / 2.0;
			angle_y_plane = CV_PI / 2.0;
		}
		else
		{
			angle_x_plane = acos(x / r_xy_plane);
			angle_y_plane = acos(y / r_xy_plane);
		}

		double  h_p2 = sqrt(1.0 - pow(r_xy_plane, 2.0));
		if (h_p2 <= 2.22507e-308)
		{
			h_p2 = 2.22507e-308;
		}

		//   double h_l = f*  () / ();

		double  lamda = f / (f + h_p2)* (f + distance) / f;//   (distance - h_p2) / h_p2;
		if (f == 0)
			lamda = 1.0;

		double  x_normal;
		double  y_normal;

		//x_normal = cos(angle_x_plane)*  lamda;
		//y_normal = cos(angle_y_plane)*  lamda;

		x_normal = x*  lamda;
		y_normal = y*  lamda;

		//return   cv::Point2d( x , y );


		return   cv::Point2d(x_normal, y_normal);
	}




};





