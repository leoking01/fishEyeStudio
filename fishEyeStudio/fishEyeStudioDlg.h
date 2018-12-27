
// fishEyeStudioDlg.h : 头文件
//

#pragma once


// CfishEyeStudioDlg 对话框
class CfishEyeStudioDlg : public CDialogEx
{
// 构造
public:
	CfishEyeStudioDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FISHEYESTUDIO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2_setIdCamera();
	afx_msg void OnBnClickedButton1_openCameraAndShow();

	int  id_camera  ;
	afx_msg void OnBnClickedButton3_undist_Image();

	void CfishEyeStudioDlg::fetchFileName(string & nameOut);
	afx_msg void OnBnClickedButton4_setMethod();

	int  id_method;
	afx_msg void OnBnClickedButton5_setDensityOfSample();

	double   densityOfSample;
	afx_msg void OnBnClickedButton7_setF();
	afx_msg void OnBnClickedButton6_setDistance();
	double distance;
	double  F;
	afx_msg void OnBnClickedButton8_setAngle_wide_camera();
	double  angle_wide_camera;

	int   CfishEyeStudioDlg::undistoredFishEyeImage(Mat img, Mat &  out,  string  nameOfImage );
	afx_msg void OnBnClickedButton9_calibrationOpencv();
	afx_msg void OnBnClickedButton10_test_calib_opencv();

private:
	const  double  rate = 1.0;// 0.3;

};
