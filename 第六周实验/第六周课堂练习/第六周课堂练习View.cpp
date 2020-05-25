
// �����ܿ�����ϰView.cpp : C�����ܿ�����ϰView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "�����ܿ�����ϰ.h"
#endif

#include "�����ܿ�����ϰDoc.h"
#include "�����ܿ�����ϰView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C�����ܿ�����ϰView

IMPLEMENT_DYNCREATE(C�����ܿ�����ϰView, CView)

BEGIN_MESSAGE_MAP(C�����ܿ�����ϰView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// C�����ܿ�����ϰView ����/����

C�����ܿ�����ϰView::C�����ܿ�����ϰView()
{
	// TODO: �ڴ˴���ӹ������
	messagepoint.x = 100;
	messagepoint.y = 100;
	Insert_state = false;

}

C�����ܿ�����ϰView::~C�����ܿ�����ϰView()
{
}

BOOL C�����ܿ�����ϰView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// C�����ܿ�����ϰView ����

void C�����ܿ�����ϰView::OnDraw(CDC* pDC)
{
	C�����ܿ�����ϰDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CString s;
	s = "ss";
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	pDC->Rectangle(90, 90, 500, 200);
	//pDC->TextOutW(110, 100, s);
}


// C�����ܿ�����ϰView ��ӡ

BOOL C�����ܿ�����ϰView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void C�����ܿ�����ϰView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void C�����ܿ�����ϰView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// C�����ܿ�����ϰView ���

#ifdef _DEBUG
void C�����ܿ�����ϰView::AssertValid() const
{
	CView::AssertValid();
}

void C�����ܿ�����ϰView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C�����ܿ�����ϰDoc* C�����ܿ�����ϰView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C�����ܿ�����ϰDoc)));
	return (C�����ܿ�����ϰDoc*)m_pDocument;
}
#endif //_DEBUG


// C�����ܿ�����ϰView ��Ϣ�������

//1) Ϊ���ռ������룬��Ҫ��Ӧ��ϢWM_CHAR����Ӻ���OnChar( )��
void C�����ܿ�����ϰView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��ʵ�ִӼ�������һ���ַ� ������ʾ��
	CClientDC dc(this);
	CString s;
	//��ȡ��������ַ�
	s.Format(_T("%c"),nChar);

	//�Ƿ�ʹ�ò��빦��
	if (Insert_state) {
		
		//�����۲죬һ��Ӣ���ַ����ռ��10�����ص㣬��ˣ��������ȷ��ѡ���ַ���λ���㷨�������뷨����
		//1.һ���ַ�ռ��10�����ص㣬Ȼ���������ʱ�򣬿��ܻ�����10�����ص����е��κ�һ��λ�ã�
		//����޶���λ�ã��������ص�����1~2ʱ��Ϊû��ѡ�е�ǰ�ַ�����ѡ��ǰһ���ַ�
		//�����ѡ�е����ص�����8~10ʱ����Ϊû��ѡ�е�ǰ�ַ�����ѡ�к�һ���ַ�
		//�����ѡ�е����ص�����3~7ʱ����Ϊѡ�е�ǰ�ַ�
		//Ŀǰ��Ϊ��ǰʵ�鲻��Ҫ��ȷ��λ�����������뷨���ϣ���ȡֱ��int����ת�����д���
		//����ʵ�����ַ����빦��ֻ���ڵ�һ���в����ַ��������еĿ��Կ���y���꣬Ŀǰ����˼����

		float position = (Insert_x - 100) / 10.0;
		//float remainder=position-int(po)
		message.Insert(int(position), s);
	
		Insert_state = false;
	}
	else {
		message += s;
	}

	//����ַ�֮������ǰ�ƶ�
	messagepoint.x+=10;

	//ʵ�ֶ��еı༭������������ַ�����һ��ʱ���޴����ŵ��ַ��Զ��Ƶ���һ��
	
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

//ʵ���ַ��Ĳ��빦�ܣ����������λ����Ϊ����㣬Ȼ��Ӽ�������һ���ַ����ַ�����
void C�����ܿ�����ϰView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Insert_x = point.x;
	Insert_y = point.y;

	Insert_state = true;

	CView::OnLButtonDown(nFlags, point);
}


void C�����ܿ�����ϰView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);

	CString s;
	s.Format(_T("����λ��,x:%d,y:%d"),point.x,point.y);

	dc.TextOutW(10, 10, s);

	CView::OnMouseMove(nFlags, point);
}
