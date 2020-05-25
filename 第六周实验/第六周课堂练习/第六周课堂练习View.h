
// 第六周课堂练习View.h : C第六周课堂练习View 类的接口
//

#pragma once


class C第六周课堂练习View : public CView
{
protected: // 仅从序列化创建
	C第六周课堂练习View();
	DECLARE_DYNCREATE(C第六周课堂练习View)

// 特性
public:
	C第六周课堂练习Doc* GetDocument() const;

// 操作
public:
	CString message;			//用于保存输入字符
	CPoint messagepoint;		//用于记录输入光标的位置
	int Insert_x, Insert_y;					//用于记录插入字符的光标位置
	bool Insert_state;			//用于控制是否使用插入功能

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~C第六周课堂练习View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 第六周课堂练习View.cpp 中的调试版本
inline C第六周课堂练习Doc* C第六周课堂练习View::GetDocument() const
   { return reinterpret_cast<C第六周课堂练习Doc*>(m_pDocument); }
#endif

