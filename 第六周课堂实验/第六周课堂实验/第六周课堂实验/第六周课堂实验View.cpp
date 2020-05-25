
// 第六周课堂实验View.cpp : C第六周课堂实验View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "第六周课堂实验.h"
#endif

#include "第六周课堂实验Doc.h"
#include "第六周课堂实验View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C第六周课堂实验View

IMPLEMENT_DYNCREATE(C第六周课堂实验View, CView)

BEGIN_MESSAGE_MAP(C第六周课堂实验View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &C第六周课堂实验View::OnFileOpen)
END_MESSAGE_MAP()

// C第六周课堂实验View 构造/析构

C第六周课堂实验View::C第六周课堂实验View()
{
	// TODO: 在此处添加构造代码
	flag = false;
}

C第六周课堂实验View::~C第六周课堂实验View()
{
}

BOOL C第六周课堂实验View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// C第六周课堂实验View 绘制

void C第六周课堂实验View::OnDraw(CDC* pDC)
{
	C第六周课堂实验Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if (flag == true)
	{
    img.Draw(pDC->m_hDC, sx, sy, w, h);
	}
}


// C第六周课堂实验View 打印

BOOL C第六周课堂实验View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void C第六周课堂实验View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void C第六周课堂实验View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// C第六周课堂实验View 诊断

#ifdef _DEBUG
void C第六周课堂实验View::AssertValid() const
{
	CView::AssertValid();
}

void C第六周课堂实验View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C第六周课堂实验Doc* C第六周课堂实验View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C第六周课堂实验Doc)));
	return (C第六周课堂实验Doc*)m_pDocument;
}
#endif //_DEBUG


// C第六周课堂实验View 消息处理程序


void C第六周课堂实验View::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	flag = true;
	CFileDialog cfd(true);
	int r = cfd.DoModal();
	CClientDC dc(this);
	if (r == IDOK)
	{
		CString filename = cfd.GetPathName();
		img.Load(filename);
		{
			CRect re;
			GetClientRect(&re);
			float re_ratio = 1.0*re.Width() / re.Height();
			float img_ratio = 1.0*img.GetWidth() / img.GetHeight();
			if (re_ratio > img_ratio)
			{
				h = re.Height(); w = img_ratio*h;
				sx = (re.Width() - w) / 2; sy = 0;
			}
			else
			{
				w = re.Width(); h = w / img_ratio;
				sx = 0; sy = (re.Height() - h) / 2;
			}
		}
		img.Draw(dc.m_hDC, sx, sy, w, h);
	}
//	Invalidate();
}
