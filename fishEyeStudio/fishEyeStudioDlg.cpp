
// fishEyeStudioDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "fishEyeStudio.h"
#include "fishEyeStudioDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CfishEyeStudioDlg 对话框



CfishEyeStudioDlg::CfishEyeStudioDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FISHEYESTUDIO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CfishEyeStudioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CfishEyeStudioDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CfishEyeStudioDlg::OnBnClickedButton2_setIdCamera)
	ON_BN_CLICKED(IDC_BUTTON1, &CfishEyeStudioDlg::OnBnClickedButton1_openCameraAndShow)
	ON_BN_CLICKED(IDC_BUTTON3, &CfishEyeStudioDlg::OnBnClickedButton3_undist_Image)
	ON_BN_CLICKED(IDC_BUTTON4, &CfishEyeStudioDlg::OnBnClickedButton4_setMethod)
	ON_BN_CLICKED(IDC_BUTTON5, &CfishEyeStudioDlg::OnBnClickedButton5_setDensityOfSample)
	ON_BN_CLICKED(IDC_BUTTON7, &CfishEyeStudioDlg::OnBnClickedButton7_setF)
	ON_BN_CLICKED(IDC_BUTTON6, &CfishEyeStudioDlg::OnBnClickedButton6_setDistance)
	ON_BN_CLICKED(IDC_BUTTON8, &CfishEyeStudioDlg::OnBnClickedButton8_setAngle_wide_camera)
	ON_BN_CLICKED(IDC_BUTTON9, &CfishEyeStudioDlg::OnBnClickedButton9_calibrationOpencv)
	ON_BN_CLICKED(IDC_BUTTON10, &CfishEyeStudioDlg::OnBnClickedButton10_test_calib_opencv)
END_MESSAGE_MAP()


// CfishEyeStudioDlg 消息处理程序

BOOL CfishEyeStudioDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	id_camera = 0;
	id_method = 2;
	densityOfSample = 0.2;// 0.45;// 0.688;// 1.0;
	distance = 0.1;;
	F = 0.005;// 0.01;// 0.5;
	angle_wide_camera = 180;



	//CString str21;
	//GetDlgItemText(IDC_EDIT2, str21);
	CString  cs;
	//SetDlgItemText(IDC_EDIT2, cs);
	//str21 = str21 + CString("\r\n");
	//cs = str21 + cs;


	cs = CString("id_camera=") + CString(to_string(id_camera).c_str()) + CString("\r\n") +

		CString("id_method=") + CString(to_string(id_method).c_str()) + CString("\r\n") +
		CString("densityOfSample=") + CString(to_string(densityOfSample).c_str()) + CString("\r\n") +
		CString("distance=") + CString(to_string(distance).c_str()) + CString("\r\n") +
		CString("F=") + CString(to_string(F).c_str()) + CString("\r\n") +
		CString("angle_wide_camera=") + CString(to_string(angle_wide_camera).c_str()) + CString("\r\n");

	SetDlgItemText(IDC_EDIT2, cs);




	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CfishEyeStudioDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CfishEyeStudioDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CfishEyeStudioDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CfishEyeStudioDlg::OnBnClickedButton2_setIdCamera()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	CString str2("0");
	GetDlgItemText(IDC_EDIT1, str2);
	//str2.
	int i = 0;
	LPTSTR lpsz;// = 20;
	lpsz = (LPTSTR)(LPCTSTR)str2;
	i = _ttoi(str2);
	//str2.Format(_T("%d"), i)   ;
	id_camera = i;

	//AfxMessageBox(_T("最大视频帧数设置完成，谢谢！ "));
	CString cstr;
	cstr.Format(_T("id_camera设置完成，谢谢！id_camera为： %d"), i);
	AfxMessageBox(cstr);

	//append_string_on_edit_controler(IDC_EDIT2, CString("id_camera设置完成，谢谢！id_camera为： ")
	//	+ CString(to_string(id_camera).c_str()));

	CString  cs = CString("id_camera设置完成，谢谢！id_camera为： ")
		+ CString(to_string(id_camera).c_str());// ("");
	CString str21;
	GetDlgItemText(IDC_EDIT2, str21);
	str21 = str21 + CString("\r\n");
	cs = str21 + cs;
	SetDlgItemText(IDC_EDIT2, cs);

}


void CfishEyeStudioDlg::OnBnClickedButton1_openCameraAndShow()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	clock_t start, end;
	start = clock();
	//…calculating…

	int  opt = 0;
	if (1)
	{
		VideoCapture  vc;
		if (opt == 0)
		{
			vc.open(this->id_camera);
			vc.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
			vc.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
		}

		//else if (opt == 1)
		//	vc.open(nameOfVideo);
		else
		{
			cout << "videoProc() ::  video open-mode wrong , please check. " << endl;
			return;
		}

		Mat  frame;
		vc >> frame;
		int  id = 0;
		while (1)
		{
			if (0)
			{
				clock_t start, end;
				start = clock();
				//procImage__maskRcnn(frame, net, id);
				end = clock();
				printf("用时：第%d帧， time=%f\n", id, ((double)end - start) / CLK_TCKCLOCKS_PER_SEC);
			}
			vc >> frame;
			id++;
			if (frame.data)
			{
				imshow("frame", frame);

				if (0 == this->id_camera)
				{
					Mat  undistored;
					this->undistoredFishEyeImage(frame, undistored, "cameraFrame");
					Mat  rsz;
					resize(undistored, rsz, Size(640, 480));
					imshow("rsz__undistored", rsz);
				}


				char  key = waitKey(200);
				if (key == 13)
					imwrite(("frame.jpg" + to_string(id) + string(".jpg")).c_str(), frame);
				else if (key > 0)
					break;
			}
		}
		vc.release();
	}


	FreeConsole();
}





void CfishEyeStudioDlg::fetchFileName(string & nameOut)
{
	CString picPath;   //定义图片路径变量  
	CFileDialog dlg(TRUE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, NULL, this);   //选择文件对话框  

	if (dlg.DoModal() == IDOK)
	{
		picPath = dlg.GetPathName();  //获取图片路径  
	}
	else
	{
		return;
	}
	if (picPath.IsEmpty())
		return;
	////CString to string  使用这个方法记得字符集选用“使用多字节字符”，不然会报错  
	//string picpath = picPath.GetBuffer(0);

	//从这里开始进行转化，这是一个宏定义
	USES_CONVERSION;
	//进行转换
	char* keyChar = T2A(picPath.GetBuffer(0));
	picPath.ReleaseBuffer();
	string picpath(keyChar);
	//string   picpath = string(keyChar);
	nameOut = picpath;
}

void CfishEyeStudioDlg::OnBnClickedButton4_setMethod()
{
	// TODO: 在此添加控件通知处理程序代码


		// TODO: 在此添加控件通知处理程序代码
	CString str2("0");
	GetDlgItemText(IDC_EDIT3, str2);
	//str2.
	int i = 0;
	LPTSTR lpsz;// = 20;
	lpsz = (LPTSTR)(LPCTSTR)str2;
	i = _ttoi(str2);
	//str2.Format(_T("%d"), i)   ;
	id_method = i;

	//AfxMessageBox(_T("最大视频帧数设置完成，谢谢！ "));
	CString cstr;
	cstr.Format(_T("id_method设置完成，谢谢！id_method为： %d"), i);
	AfxMessageBox(cstr);

	//append_string_on_edit_controler(IDC_EDIT2, CString("id_camera设置完成，谢谢！id_camera为： ")
	//	+ CString(to_string(id_camera).c_str()));

	CString  cs = CString("id_method设置完成，谢谢！id_method为： ")
		+ CString(to_string(id_method).c_str());// ("");
	CString str21;
	GetDlgItemText(IDC_EDIT2, str21);
	str21 = str21 + CString("\r\n");
	cs = str21 + cs;
	SetDlgItemText(IDC_EDIT2, cs);

}


void CfishEyeStudioDlg::OnBnClickedButton5_setDensityOfSample()
{
	// TODO: 在此添加控件通知处理程序代码

	// TODO: 在此添加控件通知处理程序代码
	CString str2("0");
	GetDlgItemText(IDC_EDIT4, str2);
	//str2.
	double  i = 0;
	LPTSTR lpsz;// = 20;
	lpsz = (LPTSTR)(LPCTSTR)str2;
	i = _ttof(str2);
	//str2.Format(_T("%d"), i)   ;
	densityOfSample = i;

	//AfxMessageBox(_T("最大视频帧数设置完成，谢谢！ "));
	CString cstr;
	cstr.Format(_T("densityOfSample设置完成，谢谢！densityOfSample为： %f"), i);
	AfxMessageBox(cstr);

	//append_string_on_edit_controler(IDC_EDIT2, CString("id_camera设置完成，谢谢！id_camera为： ")
	//	+ CString(to_string(id_camera).c_str()));

	CString  cs = CString("densityOfSample设置完成，谢谢！densityOfSample为： ")
		+ CString(to_string(densityOfSample).c_str());// ("");
	CString str21;
	GetDlgItemText(IDC_EDIT2, str21);
	str21 = str21 + CString("\r\n");
	cs = str21 + cs;
	SetDlgItemText(IDC_EDIT2, cs);
}





void CfishEyeStudioDlg::OnBnClickedButton6_setDistance()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str2("0");
	GetDlgItemText(IDC_EDIT5, str2);
	//str2.
	double  i = 0;
	LPTSTR lpsz;// = 20;
	lpsz = (LPTSTR)(LPCTSTR)str2;
	i = _ttof(str2);
	//str2.Format(_T("%d"), i)   ;
	distance = i;

	//AfxMessageBox(_T("最大视频帧数设置完成，谢谢！ "));
	CString cstr;
	cstr.Format(_T("distance 设置完成，谢谢！distance 为： %f"), i);
	AfxMessageBox(cstr);

	//append_string_on_edit_controler(IDC_EDIT2, CString("id_camera设置完成，谢谢！id_camera为： ")
	//	+ CString(to_string(id_camera).c_str()));

	CString  cs = CString("distance 设置完成，谢谢！distance 为： ")
		+ CString(to_string(distance).c_str());// ("");
	CString str21;
	GetDlgItemText(IDC_EDIT2, str21);
	str21 = str21 + CString("\r\n");
	cs = str21 + cs;
	SetDlgItemText(IDC_EDIT2, cs);
}
void CfishEyeStudioDlg::OnBnClickedButton7_setF()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	CString str2("0");
	GetDlgItemText(IDC_EDIT6, str2);
	//str2.
	double  i = 0;
	LPTSTR lpsz;// = 20;
	lpsz = (LPTSTR)(LPCTSTR)str2;
	i = _ttof(str2);
	//str2.Format(_T("%d"), i)   ;
	F = i;

	//AfxMessageBox(_T("最大视频帧数设置完成，谢谢！ "));
	CString cstr;
	cstr.Format(_T("F 设置完成，谢谢！F 为： %f"), i);
	AfxMessageBox(cstr);

	//append_string_on_edit_controler(IDC_EDIT2, CString("id_camera设置完成，谢谢！id_camera为： ")
	//	+ CString(to_string(id_camera).c_str()));

	CString  cs = CString("F 设置完成，谢谢！ F 为： ")
		+ CString(to_string(F).c_str());// ("");
	CString str21;
	GetDlgItemText(IDC_EDIT2, str21);
	str21 = str21 + CString("\r\n");
	cs = str21 + cs;
	SetDlgItemText(IDC_EDIT2, cs);
}


void CfishEyeStudioDlg::OnBnClickedButton8_setAngle_wide_camera()
{
	// TODO: 在此添加控件通知处理程序代码


	// TODO: 在此添加控件通知处理程序代码
	CString str2("0");
	GetDlgItemText(IDC_EDIT7, str2);
	//str2.
	double  i = 0;
	LPTSTR lpsz;// = 20;
	lpsz = (LPTSTR)(LPCTSTR)str2;
	i = _ttof(str2);
	//str2.Format(_T("%d"), i)   ;
	angle_wide_camera = i;

	//AfxMessageBox(_T("最大视频帧数设置完成，谢谢！ "));
	CString cstr;
	cstr.Format(_T("angle_wide_camera 设置完成，谢谢！angle_wide_camera 为： %f"), i);
	AfxMessageBox(cstr);

	//append_string_on_edit_controler(IDC_EDIT2, CString("id_camera设置完成，谢谢！id_camera为： ")
	//	+ CString(to_string(id_camera).c_str()));

	CString  cs = CString("angle_wide_camera 设置完成，谢谢！ F 为： ")
		+ CString(to_string(angle_wide_camera).c_str());// ("");
	CString str21;
	GetDlgItemText(IDC_EDIT2, str21);
	str21 = str21 + CString("\r\n");
	cs = str21 + cs;
	SetDlgItemText(IDC_EDIT2, cs);

}


int   CfishEyeStudioDlg::undistoredFishEyeImage(Mat img, Mat &  out, string nameOfsrc)
{
	Mat  src = img;
	cv::imwrite((nameOfsrc + ".src.modified.jpg").c_str(), src);

	//Spherical_equidistant_projection_model(nameOfImage);
	SphericalEquidistantProjectionModel    sep;// (0, 90, 30);
	double  angle_fishEye_camera = CV_PI*  this->angle_wide_camera / 180.0;// 160.0;  //  160度


																		   //struct derection   dr = { .angle_to_x = 0, .angle_to_y = CV_PI/2.0   };
	tp_derection  dr;
	dr.angle_to_x = 0;
	dr.angle_to_y = CV_PI / 2.0;


	assert(img.rows == img.cols);

	int  r_src = img.rows * 0.5;
	//Mat rz;
	//resize(src, rz, Size(r_src * 2, r_src * 2));
	//rz.copyTo(src);


	Mat src_compare = src.clone();
	cv::imwrite("src.jpg", src);
	cv::imshow("src", src);
	cv::waitKey(200);



	const double  radius_src_standard = (src.rows / 2.0) *   (CV_PI / angle_fishEye_camera);


	double  scaleRate = 1.0;
	double  densityOfSample = this->densityOfSample;// 1.0;   // 0.1;// 0.10;// 0.02;// 0.1;
	double  distance = this->distance;// 1.0;
	int     id_method_pro = this->id_method;
	double  f = this->F;// 0.005;


	int  r_dst;
	if (f != 0)
	{
		r_dst = r_src * (1.0 + distance / f);// 900;// 6900;    // 3000;// 1200;// 800;
		//r_dst = max(r_dst, 4000);
		r_dst = min(r_dst, 9000);
	}

	if (0 == f)
		r_dst = r_src;
	Mat dst = Mat(Size(r_dst * 2, r_dst * 2), CV_8UC3, Scalar(0, 0, 0));
	dst.setTo(0);


	CString str21;
	GetDlgItemText(IDC_EDIT2, str21);
	//str21 = str21 + CString("\r\n");
	CString  cs =
		CString("r_src = ")
		+ CString(to_string(r_src).c_str())
		+ CString(", r_dst = ")
		+ CString(to_string(r_dst).c_str());
	cs = str21 + CString("\r\n") + cs;
	SetDlgItemText(IDC_EDIT2, cs);

	const  double   rate_modi = 1.0;// 1.0 / sqrt(2.0);

	for (double i = 0; i < src.rows; i += densityOfSample)
	{
		for (double j = 0; j < src.cols; j += densityOfSample)
		{
			cv::Point2d  pd((i - r_src) / radius_src_standard  * rate_modi, (j - r_src) / radius_src_standard  * rate_modi);
			if (pow(pd.x, 2.0) + pow(pd.y, 2.0) > 1.0)
			{
				src_compare.at<Vec3b>((int)i, (int)j)[0] = 0;
				src_compare.at<Vec3b>((int)i, (int)j)[1] = 128;
				src_compare.at<Vec3b>((int)i, (int)j)[2] = 0;

				continue;
			}

			tp_derection dr_fall;
			cv::Point2d   pd_update;

			if (0 == id_method_pro)//历史上最无用的变换,复原算法
			{
				dr_fall = sep.fall__descartesToSphere(pd, 1);
				pd_update = sep.fall__sphereToDescartes(dr_fall, 1);
			}

			else if (1 == id_method_pro)   //   投影直投方式
			{
				dr_fall = sep.fall__descartesToSphere(pd, 1);
				pd_update = sep.fall__sphere_2_Descartes__ImagePlane(dr_fall, 1, distance, f);
			}
			else if (2 == id_method_pro)   // 等距投影的方式
			{
				dr_fall = sep.equiDistance__descartes_2_Sphere(pd, 1);
				pd_update = sep.equiDistance__sphere_2_Descartes__ImagePlane(dr_fall, 1, distance, f);
			}
			else
				continue;

			double   x_u = pd_update.x*  dst.rows*0.5* scaleRate + dst.rows  *0.5;
			double   y_u = pd_update.y*  dst.cols*0.5* scaleRate + dst.cols  *0.5;

			if (x_u >= 0
				&& y_u >= 0
				&& x_u <= (dst.rows - 1)  // *  (   angle_fishEye_camera / CV_PI )
				&& y_u <= (dst.cols - 1)  // *  (   angle_fishEye_camera / CV_PI ) 
				)
			{
				dst.at<Vec3b>((int)x_u, (int)y_u)[0] = src.at<Vec3b>((int)i, (int)j)[0];
				dst.at<Vec3b>((int)x_u, (int)y_u)[1] = src.at<Vec3b>((int)i, (int)j)[1];
				dst.at<Vec3b>((int)x_u, (int)y_u)[2] = src.at<Vec3b>((int)i, (int)j)[2];

				src_compare.at<Vec3b>((int)i, (int)j)[0] = 0;
				src_compare.at<Vec3b>((int)i, (int)j)[1] = 0;
				src_compare.at<Vec3b>((int)i, (int)j)[2] = 0;
			}
			else
			{
				src_compare.at<Vec3b>((int)i, (int)j)[0] = 128;
				src_compare.at<Vec3b>((int)i, (int)j)[1] = 0;
				src_compare.at<Vec3b>((int)i, (int)j)[2] = 255;
			}
		}
	}

	string  nameOfResult = nameOfsrc + "_method_" + to_string(id_method_pro) + "_distance_" + to_string(distance) + "_f_" + to_string(f)
		+ "_densityOfSample_" + to_string(densityOfSample)
		+ "_angleWideCamera_" + to_string(angle_wide_camera);
	cv::imwrite((nameOfResult + "_undistored.png").c_str(), dst);
	cv::imwrite((nameOfResult + "_src_compare.png").c_str(), src_compare);

	cv::imshow((nameOfResult + "_undistored.png").c_str(), dst);
	cv::imshow((nameOfResult + "_src_compare.png").c_str(), src_compare);

	cv::waitKey(200);
	out = dst;

	return 0;
}




void trans_src_2_dst(Mat src, Mat &  dst)
{
	//  resize
	if (0)
	{
		resize(src, dst, Size(dst.cols, dst.rows));
		return;
	}

	// not resize 
	if (!src.data)
		return;
	int  r_src = src.rows;
	int  c_src = src.cols;

	int  r_dst = dst.rows;
	int  c_dst = dst.cols;

	//LOG4CPLUS_DEBUG(test1_01,
	//	"src, dst , r_src= " << r_src << ",c_src=" << c_src << ",r_dst=" << r_dst << ",c_dst=" << c_dst);

	if (r_src <= 0 || c_src <= 0)
		return;
	double rate_r = (float)r_dst / (float)r_src;
	double rate_c = (float)c_dst / (float)c_src;

	float rate = min(rate_r, rate_c);
	//LOG4CPLUS_DEBUG(test1_01,
	//	"src, dst , rate_r= " << rate_r << ",rate_c=" << rate_c << ",rate=" << rate);



	int r_act = (int)(rate* r_src);
	int c_act = (int)(rate* c_src);
	//LOG4CPLUS_DEBUG(test1_01,
	//	" r_act= " << r_act << ",c_act=" << c_act);

	if (0)
	{
		char  car[900];
		sprintf(car, "r_src, c_src, r_dst, c_dst, r_act , c_act = %d,  %d, %d,  %d, %d,  %d  ", r_src, c_src, r_dst, c_dst, r_act, c_act);
		//LOG_DEBUG(car);
	}



	Mat tmp;
	resize(src, tmp, Size(c_act, r_act));
	//tmp.copyTo(src);

	int x_rt = (int)(c_dst / 2 - c_act / 2);
	int y_rt = (int)(r_dst / 2 - r_act / 2);

	//LOG4CPLUS_DEBUG(test1_01, "trans_src_2_dst,Rect rt, x_rt= " << x_rt << ",y_rt=" << y_rt << ",c_act=" << c_act << ",r_act=" << r_act);
	Rect rt = Rect(x_rt, y_rt, c_act, r_act);
	dst.setTo(Scalar(255, 128, 0));
	tmp.copyTo(dst(rt));

	//LOG4CPLUS_DEBUG(test1_01, "拷贝成功： tmp.copyTo(dst(rt))。   ");
}


void CfishEyeStudioDlg::OnBnClickedButton3_undist_Image()
{
	// TODO: 在此添加控件通知处理程序代码
	AllocConsole();
	freopen("CONOUT$", "w", stdout);




	int opt_solution = 0;

	//多项式法，但是这里暂时不清楚多项式系数从哪里来的，（猜测）也许是手工提取的匹配点，再解方程。
	if (opt_solution == 1)
	{
		string  nameOfImage;
		fetchFileName(nameOfImage);
		if (nameOfImage.size() <= 0)
			return;

		main_fishEye_distored(nameOfImage);

		CString str21;
		GetDlgItemText(IDC_EDIT2, str21);
		//str21 = str21 + CString("\r\n");
		CString  cs =
			CString("去除畸变完成：多项式算法。");
		cs = str21 + CString("\r\n") + cs;
		SetDlgItemText(IDC_EDIT2, cs);

	}


	//
	//球面等距投影模型
	//Spherical equidistant projection model
	if (opt_solution == 0)
	{
		string  nameOfImage;
		fetchFileName(nameOfImage);
		if (nameOfImage.size() <= 0)
			return;


		//int rows = 400;
		//int cols = 400;
		cv::Mat  src;// (rows, cols, CV_8UC3, Scalar(0, 0, 0));
		src = imread(nameOfImage);


		double  rate_pre = 640.0 / src.cols;
		Mat  smaller;
		resize(src, smaller, Size(src.cols* rate_pre, src.rows*  rate_pre));
		smaller.copyTo(src);



		int  leng;// = max(src.rows, src.cols);
		if (1)
		{
			leng = max(src.rows, src.cols);
			Mat  dst(leng, leng, CV_8UC3, Scalar(255, 128, 0));
			trans_src_2_dst(src, dst);
			dst.copyTo(src);
		}
		//


		if (0)
		{
			leng = (int)(sqrt(pow(src.rows*0.5, 2.0) + pow(src.cols*0.5, 2.0)) *  2.0 + 0.5);
			Mat  dst(leng, leng, CV_8UC3, Scalar(255, 128, 0));

			Rect  rt(dst.cols / 2.0 - src.cols *0.5, dst.rows / 2.0 - src.rows *0.5, src.cols, src.rows);
			src.copyTo(dst(rt));
			dst.copyTo(src);
		}



		Mat out;
		this->undistoredFishEyeImage(src, out, nameOfImage);



		CString str21;
		GetDlgItemText(IDC_EDIT2, str21);
		//str21 = str21 + CString("\r\n");
		CString  cs =
			CString("去除畸变完成：等距投影算法。");
		cs = str21 + CString("\r\n") + cs;
		SetDlgItemText(IDC_EDIT2, cs);


	}


	FreeConsole();
}



#include <opencv2\opencv.hpp>
#include <fstream>
using namespace std;
using namespace cv;

int calibrate_camera_opencv_proc(string nameTxtFileInput, string  nameTxtFileSave,double  rateV)
{
	fstream   fin(nameTxtFileInput, ios::in);
	vector<string  >  vctImages;
	while (!fin.eof())
	{
		string  nameOfImage;
		fin >> nameOfImage;
		vctImages.push_back(nameOfImage);
	}
	cout << "nameTxtFileInput = " << nameTxtFileInput << endl;
	cout << "vctImages.size() = " << vctImages.size() << endl;
	
	fin.close();


						     /************************************************************************
								   读取每一幅图像，从中提取出角点，然后对角点进行亚像素精确化
							  *************************************************************************/
	cout << "开始提取角点………………" << endl;
	//以下三行为需要手动修改的参数
	int image_count = vctImages.size();//  14;                   //图像数量
	Size board_size = Size(9, 6);            //定标板上每行、列的角点数
	board_size = Size(6, 4);            //定标板上每行、列的角点数
	int x_expand = 0, y_expand = 200;		//x,y方向的扩展(x横向，y纵向)，适当增大可以不损失原图像信息
	x_expand = 200;
	y_expand = 300;
	Mat  getSz = imread(vctImages[0]);
	double  rate = rateV;// 1.0;// 0.50;
	x_expand = getSz.cols * rate;
	y_expand = getSz.rows * rate;



	//ofstream fout("caliberation_result.txt");
	nameTxtFileSave = nameTxtFileSave + ".rate." + to_string(rate) + ".jpg";
	ofstream fout(nameTxtFileSave);  /**    保存定标结果的文件     **/

	cout << "nameTxtFileSave = " << nameTxtFileSave << endl;



	vector<Point2f> corners;                //缓存每幅图像上检测到的角点
	vector<vector<Point2f>>  corners_Seq;   //保存检测到的所有角点/   
	vector<Mat>  image_Seq;
	int successImageNum = 0;				//成功提取角点的棋盘图数量	
	bool conner_flag = true;				//所有图像角点提取成功为true，其余为false
	for (int i = 0; i != image_count; i++)
	{
		cout << "img" << i + 1 << "..." << endl;
		string  nameOfImageItem;

		if (0)
		{
			string imageFileName;
			std::stringstream StrStm;
			StrStm << i + 1;
			StrStm >> imageFileName;
			imageFileName += ".jpg";
			nameOfImageItem = "img" + imageFileName;
		}
		nameOfImageItem = vctImages[i];
		cv::Mat imageSrc = imread(nameOfImageItem);
		Mat image;//边界扩展后的图片
		copyMakeBorder(imageSrc, image, (int)(y_expand / 2), (int)(y_expand / 2), (int)(x_expand / 2), (int)(x_expand / 2), BORDER_CONSTANT);

		/* 提取角点 */
		Mat imageGray;
		cvtColor(image, imageGray, CV_RGB2GRAY);
		bool patternfound = findChessboardCorners(image, board_size, corners, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE +
			CALIB_CB_FAST_CHECK);
		if (!patternfound)
		{
			cout << "img" << i + 1 << "角点提取失败，请删除该图片，重新排序后再次运行程序！" << endl;
			conner_flag = false;
			break;
		}
		else
		{
			/* 亚像素精确化 */
			cornerSubPix(imageGray, corners, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
			/* 绘制检测到的角点并保存 */
			Mat imageTemp = image.clone();
			for (int j = 0; j < corners.size(); j++)
			{
				circle(imageTemp, corners[j], 10, Scalar(0, 0, 255), 2, 8, 0);
			}
			string imageFileName;
			if (0)
			{
				std::stringstream StrStm;
				StrStm << i + 1;
				StrStm >> imageFileName;
				imageFileName += "_corner.jpg";
				imageFileName = "corner__" + imageFileName;
			}
			imageFileName = nameTxtFileInput + "." + "corner." + to_string(i) + ".txt";
			imwrite(imageFileName.c_str(), imageTemp);
			cout << "img" << i + 1 << " 角点提取完毕" << endl;

			successImageNum = successImageNum + 1;
			corners_Seq.push_back(corners);
		}
		image_Seq.push_back(image);
	}
	if (!conner_flag)//如果有提取失败的标定图，退出程序
	{
		system("pause");
		return 0;
	}
	cout << "角点提取完成！" << endl;


	/************************************************************************
	摄像机定标
	*************************************************************************/
	cout << "开始定标………………" << endl;
	Size square_size = Size(20, 20);
	vector<vector<Point3f>>  object_Points;        /****  保存定标板上角点的三维坐标   ****/

	vector<int>  point_counts;
	/* 初始化定标板上角点的三维坐标 */
	for (int t = 0; t < successImageNum; t++)
	{
		vector<Point3f> tempPointSet;
		for (int i = 0; i < board_size.height; i++)
		{
			for (int j = 0; j < board_size.width; j++)
			{
				/* 假设定标板放在世界坐标系中z=0的平面上 */
				Point3f tempPoint;
				tempPoint.x = i*square_size.width;
				tempPoint.y = j*square_size.height;
				tempPoint.z = 0;
				tempPointSet.push_back(tempPoint);
			}
		}
		object_Points.push_back(tempPointSet);
	}
	for (int i = 0; i < successImageNum; i++)
	{
		point_counts.push_back(board_size.width*board_size.height);
	}
	/* 开始定标 */
	Size image_size = image_Seq[0].size();
	cv::Matx33d intrinsic_matrix;    /*****    摄像机内参数矩阵    ****/
	cv::Vec4d distortion_coeffs;     /* 摄像机的4个畸变系数：k1,k2,k3,k4*/
	std::vector<cv::Vec3d> rotation_vectors;                           /* 每幅图像的旋转向量 */
	std::vector<cv::Vec3d> translation_vectors;                        /* 每幅图像的平移向量 */
	int flags = 0;
	flags |= cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC;
	flags |= cv::fisheye::CALIB_CHECK_COND;
	flags |= cv::fisheye::CALIB_FIX_SKEW;
	fisheye::calibrate(object_Points, corners_Seq, image_size,
		intrinsic_matrix, distortion_coeffs, rotation_vectors, translation_vectors,
		flags, cv::TermCriteria(3, 20, 1e-6)
	);
	cout << "定标完成！\n";



	/************************************************************************
	对定标结果进行评价
	*************************************************************************/
	cout << "开始评价定标结果………………" << endl;
	double total_err = 0.0;                   /* 所有图像的平均误差的总和 */
	double err = 0.0;                        /* 每幅图像的平均误差 */
	vector<Point2f>  image_points2;             /****   保存重新计算得到的投影点    ****/

	cout << "每幅图像的定标误差：" << endl;
	cout << "每幅图像的定标误差：" << endl << endl;
	for (int i = 0; i < image_count; i++)
	{
		vector<Point3f> tempPointSet = object_Points[i];
		/****    通过得到的摄像机内外参数，对空间的三维点进行重新投影计算，得到新的投影点     ****/
		fisheye::projectPoints(tempPointSet, image_points2, rotation_vectors[i], translation_vectors[i], intrinsic_matrix, distortion_coeffs);
		/* 计算新的投影点和旧的投影点之间的误差*/
		vector<Point2f> tempImagePoint = corners_Seq[i];
		Mat tempImagePointMat = Mat(1, tempImagePoint.size(), CV_32FC2);
		Mat image_points2Mat = Mat(1, image_points2.size(), CV_32FC2);
		for (size_t i = 0; i != tempImagePoint.size(); i++)
		{
			image_points2Mat.at<Vec2f>(0, i) = Vec2f(image_points2[i].x, image_points2[i].y);
			tempImagePointMat.at<Vec2f>(0, i) = Vec2f(tempImagePoint[i].x, tempImagePoint[i].y);
		}
		err = norm(image_points2Mat, tempImagePointMat, NORM_L2);
		total_err += err /= point_counts[i];
		cout << "第" << i + 1 << "幅图像的平均误差：" << err << "像素" << endl;
		fout << "第" << i + 1 << "幅图像的平均误差：" << err << "像素" << endl;
	}
	cout << "总体平均误差：" << total_err / image_count << "像素" << endl;
	fout << "总体平均误差：" << total_err / image_count << "像素" << endl << endl;
	cout << "评价完成！" << endl;




	/************************************************************************
	保存定标结果
	*************************************************************************/
	cout << "开始保存定标结果………………" << endl;
	Mat rotation_matrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* 保存每幅图像的旋转矩阵 */

	fout << "相机内参数矩阵：" << endl;
	fout << intrinsic_matrix << endl;
	fout << "畸变系数：\n";
	fout << distortion_coeffs << endl;
	for (int i = 0; i < image_count; i++)
	{
		fout << "第" << i + 1 << "幅图像的旋转向量：" << endl;
		fout << rotation_vectors[i] << endl;

		/* 将旋转向量转换为相对应的旋转矩阵 */
		Rodrigues(rotation_vectors[i], rotation_matrix);
		fout << "第" << i + 1 << "幅图像的旋转矩阵：" << endl;
		fout << rotation_matrix << endl;
		fout << "第" << i + 1 << "幅图像的平移向量：" << endl;
		fout << translation_vectors[i] << endl;
	}
	cout << "完成保存" << endl;
	fout << endl;


	/************************************************************************
	显示定标结果
	*************************************************************************/
	Mat mapx = Mat(image_size, CV_32FC1);
	Mat mapy = Mat(image_size, CV_32FC1);
	Mat R = Mat::eye(3, 3, CV_32F);
	cout << "保存矫正图像" << endl;
	for (int i = 0; i != image_count; i++)
	{
		fisheye::initUndistortRectifyMap(intrinsic_matrix, distortion_coeffs, R, intrinsic_matrix, image_size, CV_32FC1, mapx, mapy);
		Mat t = image_Seq[i].clone();
		cv::remap(image_Seq[i], t, mapx, mapy, INTER_LINEAR);
		string imageFileName;

		if (0)
		{
			std::stringstream StrStm;
			StrStm << i + 1;
			StrStm >> imageFileName;
			imageFileName += "_d.jpg";
			imageFileName = "u__" + imageFileName;
		}


		imageFileName = nameTxtFileInput + "." + "u_dist." + to_string(i) + ".jpg";

		imwrite(imageFileName.c_str(), t);

		if (i % 10 == 0)
			imshow(imageFileName, t);
		cout << imageFileName  << "保存" << endl;
	}
	cout << "保存结束" << endl;

	//fo_intrinsic_matrix.convert
	fstream   fo_intrinsic_matrix(nameTxtFileInput +"."+ "innerPara__intrinsic_matrix.txt." + to_string(rate) + ".yml", ios::out);
	fo_intrinsic_matrix << intrinsic_matrix;// << endl;;
	fo_intrinsic_matrix.close();

	fstream   fo_distortion_coeffs(nameTxtFileInput + "." + "innerPara__distortion_coeffs.txt." + to_string(rate) + ".yml", ios::out);
	fo_distortion_coeffs << distortion_coeffs << endl;;
	fo_distortion_coeffs.close();

	FileStorage  fs_mapx(nameTxtFileInput + "." + "innerPara__mapx.yml." + to_string(rate) + ".yml", FileStorage::WRITE);
	fs_mapx << "mapx" << mapx;
	fs_mapx.release();

	FileStorage  fs_mapy(nameTxtFileInput + "." + "innerPara__mapy.yml." + to_string(rate) + ".yml", FileStorage::WRITE);
	fs_mapy << "mapy" << mapy;
	fs_mapy.release();

	FileStorage  fs_R(nameTxtFileInput + "." + "innerPara__R.yml." + to_string(rate) + ".yml", FileStorage::WRITE);
	fs_R << "R" << R;
	fs_R.release();





	/************************************************************************
	测试一张图片
	*************************************************************************/
	if (1)
	{
		cout << "TestImage ..." << endl;
		Mat image = imread(vctImages[0], 1);
		Mat testImage;
		copyMakeBorder(image, testImage, (int)(y_expand / 2), (int)(y_expand / 2), (int)(x_expand / 2), (int)(x_expand / 2), BORDER_CONSTANT);
		fisheye::initUndistortRectifyMap(intrinsic_matrix, distortion_coeffs, R, intrinsic_matrix, image_size, CV_32FC1, mapx, mapy);
		Mat t = testImage.clone();
		cv::remap(testImage, t, mapx, mapy, INTER_LINEAR);

		imwrite((nameTxtFileInput + "TestOutput.jpg").c_str(), t);
		imshow(nameTxtFileInput + "TestOutput.jpg", t);
		cout << "保存结束    程序结束。" << endl;
	}
	while (1)
	{
		if (cvWaitKey(15) == 27)
		{
			break;
		}
	}

	return 0;
}


void CfishEyeStudioDlg::OnBnClickedButton9_calibrationOpencv()
{
	// TODO: 在此添加控件通知处理程序代码
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	string nameTxtFileInput;
	fetchFileName(nameTxtFileInput);

	string  nameTxtFileSave = nameTxtFileInput + ".result_calib.txt";
	calibrate_camera_opencv_proc(nameTxtFileInput, nameTxtFileSave,this->rate  );

	FreeConsole();
}


void CfishEyeStudioDlg::OnBnClickedButton10_test_calib_opencv()
{
	// TODO: 在此添加控件通知处理程序代码
	AllocConsole();
	freopen("CONOUT$", "w", stdout);


	cv::Matx33d intrinsic_matrix;    /*****    摄像机内参数矩阵    ****/
	cv::Vec4d distortion_coeffs;     /* 摄像机的4个畸变系数：k1,k2,k3,k4*/
	Mat  mapx, mapy;
	Mat R;

	string nameTxtFileInput;
	if (this->id_camera == 2)
		nameTxtFileInput = "D:\\projects_fishEye\\fishEyeStudio\\fishEyeStudio\\imgCalibOpencv/calibInput_2_160_fishEye.txt";
	else if (this->id_camera == 1)
		nameTxtFileInput = "D:\\projects_fishEye\\fishEyeStudio\\fishEyeStudio\\imgCalibOpencv/calibInput_1_130_fishEye.txt";
	else if (this->id_camera == 0)
		nameTxtFileInput = "D:\\projects_fishEye\\fishEyeStudio\\fishEyeStudio\\imgCalibOpencv/calibInput_0_0_fishEye.txt";
	else
	{
		cout << "找不到模型配置文件，请确保配置正确。" << endl;
		return;
	}
		
	cout << "id_camera = " << id_camera << endl;
	cout << "nameTxtFileInput = " << nameTxtFileInput<<   endl;

//#ifdef  no_def_no
#ifdef no_def_no
	fstream   fo_intrinsic_matrix(nameTxtFileInput + "." + "innerPara__intrinsic_matrix.txt", ios::in);
	fo_intrinsic_matrix  >> intrinsic_matrix;// << endl;;
	fo_intrinsic_matrix.close();

	fstream   fo_distortion_coeffs(nameTxtFileInput + "." + "innerPara__distortion_coeffs.txt", ios::in);
	fo_distortion_coeffs >> distortion_coeffs;// << endl;;
	fo_distortion_coeffs.close();

	FileStorage  fs_R(nameTxtFileInput + "." + "innerPara__R.yml", FileStorage::READ);
	fs_R["R"] >> R;
	fs_R.release();
#endif

	FileStorage  fs_mapx(nameTxtFileInput + "." + "innerPara__mapx.yml", FileStorage::READ);
	fs_mapx["mapx"] >>    mapx;
	fs_mapx.release();

	FileStorage  fs_mapy(nameTxtFileInput + "." + "innerPara__mapy.yml", FileStorage::READ);
	fs_mapy["mapy"]   >> mapy;
	fs_mapy.release();




	//下面的两个数值 以及图片的大小应当与训练的时候的保持一致，需要细细检查!!!
	int x_expand = 0, y_expand = 200;		//x,y方向的扩展(x横向，y纵向)，适当增大可以不损失原图像信息



	/************************************************************************
	测试一张图片
	*************************************************************************/
	if (1)
	{
		string nameTxtFileInput;
		fetchFileName(nameTxtFileInput);

		cout << "TestImage ..." << endl;
		Mat image = imread(nameTxtFileInput, 1);
		if (!image.data)
			return;

		double  rate = this->rate;// 1.0;// 0.50;

		x_expand = image.cols *  rate;
		y_expand = image.rows   *  rate;


		Mat testImage;
		copyMakeBorder(image, testImage, (int)(y_expand / 2), (int)(y_expand / 2), (int)(x_expand / 2), (int)(x_expand / 2), BORDER_CONSTANT);
		//fisheye::initUndistortRectifyMap(intrinsic_matrix, distortion_coeffs, R, intrinsic_matrix, image_size, CV_32FC1, mapx, mapy);
		Mat t = testImage.clone();
		cv::remap(testImage, t, mapx, mapy, INTER_LINEAR);

		imwrite((nameTxtFileInput + "TestOutput.jpg.txt.jpg").c_str(), t);
		imshow(nameTxtFileInput + "TestOutput.jpg.txt.jpg", t);
		cout << "保存结束 .program  all  finish . " << endl;
	}


	FreeConsole();
}
