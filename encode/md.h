#ifndef __MD_H__
#define __MD_H__

#define MAX_MACROCELL_NUM		1620     // = (720*576)/(16*16) = D1�����ص�/һ���������ص�
#define MOVE_FRAME_INTERVAL		5

/* ��Ƶ�ƶ����� */
typedef struct _MdArea_
{
	ushort	area[12];
} MD_AREA_T;

typedef struct _Md_Attr_
{
	unsigned int    macroThreshold;     /* �����ֵ */
	unsigned int 	macroRatio;         /* �����б��������� */
	unsigned char	frameCount;         // �ۼ��ж���֡��⵽�ƶ����
	unsigned char	wBlock;             // ����ܹ��ж��ٸ�ģ��(16 ������һ��ģ��)
	unsigned char	hBlock;             // �߶��ܹ��ж��ٸ�ģ��
	unsigned char	mask[MAX_MACROCELL_NUM];   /* �����ƶ���������Ӧ�ĺ��� */
	unsigned int	sadSum[MAX_MACROCELL_NUM];
} MD_ATTR_T;

void StartMdThread();
void StopMdThread();
void MdSendMsgChangeParam();

#endif 

