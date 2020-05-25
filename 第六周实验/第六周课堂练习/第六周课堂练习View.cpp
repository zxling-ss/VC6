
// 第六周课堂练习View.cpp : C第六周课堂练习View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "第六周课堂练习.h"
#endif

#include "第六周课堂练习Doc.h"
#include "第六周课堂练习View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C第六周课堂练习View

IMPLEMENT_DYNCREATE(C第六周课堂练习View, CView)

BEGIN_MESSAGE_MAP(C第六周课堂练习View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// C第六周课堂练习View 构造/析构

C第六周课堂练习View::C第六周课堂练习View()
{
	// TODO: 在此处添加构造代码
	messagepoint.x = 100;
	messagepoint.y = 100;
	Insert_state = false;

}

C第六周课堂练习View::~C第六周课堂练习View()
{
}

BOOL C第六周课堂练习View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// C第六周课堂练习View 绘制

void C第六周课堂练习View::OnDraw(CDC* pDC)
{
	C第六周课堂练习Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CString s;
	s = "ss";
	// TODO: 在此处为本机数据添加绘制代码
	pDC->Rectangle(90, 90, 500, 200);
	//pDC->TextOutW(110, 100, s);
}


// C第六周课堂练习View 打印

BOOL C第六周课堂练习View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void C第六周课堂练习View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void C第六周课堂练习View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// C第六周课堂练习View 诊断

#ifdef _DEBUG
void C第六周课堂练习View::AssertValid() const
{
	CView::AssertValid();
}

void C第六周课堂练习View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C第六周课堂练习Doc* C第六周课堂练习View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C第六周课堂练习Doc)));
	return (C第六周课堂练习Doc*)m_pDocument;
}
#endif //_DEBUG


// C第六周课堂练习View 消息处理程序

//1) 为接收键盘输入，需要响应消息WM_CHAR，添加函数OnChar( )；
void C第六周课堂练习View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//先实现从键盘输入一个字符 ，并显示；
	CClientDC dc(this);
	CString s;
	//获取到输入的字符
	s.Format(_T("%c"),nChar);

	//是否使用插入功能
	if (Insert_state) {
		
		//经过观察，一个英文字符大概占据10个像素点，因此，设计以下确定选中字符的位置算法，具体想法如下
		//1.一个字符占据10个像素点，然而鼠标点击的时候，可能会落在10个像素点其中的任何一个位置，
		//因此限定其位置，当其像素点落在1~2时认为没有选中当前字符而是选中前一个字符
		//当鼠标选中的像素点落在8~10时，认为没有选中当前字符而是选中后一个字符
		//当鼠标选中的像素点落在3~7时，认为选中当前字符
		//目前认为当前实验不需要精确定位，所以以上想法作废，采取直接int类型转换自行处理
		//本次实验中字符插入功能只能在第一行中插入字符，其他行的可以考虑y坐标，目前懒得思考了

		float position = (Insert_x - 100) / 10.0;
		//float remainder=position-int(po)
		message.Insert(int(position), s);
	
		Insert_state = false;
	}
	else {
		message += s;
	}

	//输出字符之后光标往前移动
	messagepoint.x+=10;

	//实现多行的编辑器，当输入的字符填满一行时，无处安放的字符自动移到下一行
	
	if (messagepoint.x >=490) {
	/*	message.Append('\n');*/
		message += _T("\n");
		messagepoint.x = 100;
		//dc.TextOutW(100, 100, message);
	}
	dc.DrawText(message, CRect(100, 100, 490, 190), DT_LEFT);
	
	/*messagepoint.y++;*/
	

	CView::OnChar(nChar, nRepCnt, nFlags);
}

//实现字符的插入功能：　以鼠标点击位置作为插入点，然后从键盘输入一个字符到字符串中
void C第六周课堂练习View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Insert_x = point.x;
	Insert_y = point.y;

	Insert_state = true;

	CView::OnLButtonDown(nFlags, point);
}


void C第六周课堂练习View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);

	CString s;
	s.Format(_T("鼠标的位置,x:%d,y:%d"),point.x,point.y);

	dc.TextOutW(10, 10, s);

	CView::OnMouseMove(nFlags, point);
}
