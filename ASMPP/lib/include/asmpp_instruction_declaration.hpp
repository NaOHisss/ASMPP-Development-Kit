#ifndef ASMPP_INSTRUCTION_DECLARATION
#define ASMPP_INSTRUCTION_DECLARATION

IS_DEF(ASMPP,16)

/*�Ĵ�������*/
        //�������������Ĵ���
        INS_BEGIN(ASMPP,LDRIV,0x00000000,RN)
            REG_VAL(0)=NUM_VAL(1);
        INS_END(LDRIV)
        //���ڴ���ص��Ĵ���
        INS_BEGIN(ASMPP,LD2RFM,0x00000001,RM)
            REG_VAL(0)=MEM_VAL(1);
        INS_END(LD2RFM)
        //�ӼĴ������ص��ڴ�
        INS_BEGIN(ASMPP,LD2MFR,0x00000002,MR)
            MEM_VAL(0)=REG_VAL(1);
        INS_END(LD2MFR)
/*�ڴ����*/
        //�ƶ�����
        INS_BEGIN(ASMPP,MOV,0x00000003,MM)
            MEM_VAL(0)=MEM_VAL(1);
        INS_END(MOV)
/*���ݲ���*/
        //����int�ͱ���

        //����boolean�ͱ���

/*��������*/
        //�ӷ����������Ĵ���
        INS_BEGIN(ASMPP,ADDR,0x00000004,RRR)
            REG_VAL(0)=REG_VAL(1)+REG_VAL(2);
        INS_END(ADDR)
        //����
        INS_BEGIN(ASMPP,SUBR,0x00000005,RRR)
            REG_VAL(0)=REG_VAL(1)-REG_VAL(2);
        INS_END(SUBR)
        //�˷�
        INS_BEGIN(ASMPP,MULR,0x00000006,RRR)
            REG_VAL(0)=REG_VAL(1)*REG_VAL(2);
        INS_END(MULR)
        //����
        INS_BEGIN(ASMPP,DIVR,0x00000007,RRR)
            REG_VAL(0)=REG_VAL(1)/REG_VAL(2);
        INS_END(DIVR)
        //����
        INS_BEGIN(ASMPP,MODR,0x00000008,RRR)
            REG_VAL(0)=REG_VAL(1)%REG_VAL(2);
        INS_END(MODR)
        //����int
        INS_BEGIN(ASMPP,INC,0x00000009,R)
            REG_VAL(0)++;
        INS_END(INC)
/*���ñ�ݺ���*/
        INS_BEGIN(ASMPP,PRINTR,0x0000000A,R)
            std::cout<<REG_VAL(0);
        INS_END(PRINTR)

        INS_BEGIN(ASMPP,PRINTRLN,0x0000000B,R)
            std::cout<<REG_VAL(0)<<std::endl;
        INS_END(PRINTRLN)

        INS_BEGIN(ASMPP,PRINTM,0x0000000C,M)
            std::cout<<MEM_VAL(0);
        INS_END(PRINTM)

        INS_BEGIN(ASMPP,PRINTMLN,0x0000000D,M)
            std::cout<<MEM_VAL(0)<<std::endl;
        INS_END(PRINTMLN)

        INS_BEGIN(ASMPP,PRINTN,0x0000000E,N)
            std::cout<<NUM_VAL(0);
        INS_END(PRINTN)

        INS_BEGIN(ASMPP,PRINTNLN,0x0000000F,N)
            std::cout<<NUM_VAL(0)<<std::endl;
        INS_END(PRINTNLN)

#endif //ASMPP_INSTRUCTION_DECLARATION
