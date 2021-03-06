#ifndef UTILITIES_STRING
#define UTILITIES_STRING

#include "array.hpp"

using namespace utilities::array;

namespace utilities
{
    namespace string
    {
        constexpr int getLengthOfCharArray(const char *str)
        {
            int len=0;
            while(*(str+len)!='\0')++len;
            return len;
        }

        template<bool delete_array_when_destruct=false>
        struct String:public Array<const char,delete_array_when_destruct>
        {
            String():Array<const char,delete_array_when_destruct>() {}
            String(const Array<const char> &arr):Array<const char,delete_array_when_destruct>(arr) {}
            String(Array<const char> &&arr):Array<const char,delete_array_when_destruct>(arr) {}
            String(const Array<char> &arr)
            {
                this->arr_ptr=arr.arr_ptr;
                this->length=getLengthOfCharArray(this->arr_ptr);
            }
            String(Array<char> &&arr)
            {
                this->arr_ptr=arr.arr_ptr;
                arr.arr_ptr=nullptr;
                this->length=getLengthOfCharArray(this->arr_ptr);
            }
            String(const char *str)
            {
                this->arr_ptr=str;
                this->length=getLengthOfCharArray(str);
            }
            String(char *arr,int len):Array<const char,delete_array_when_destruct>(arr,len) {}
            template<int L>
            String(char (&arr)[L]):Array<const char,delete_array_when_destruct>(arr) {}
            inline const char * getCharArray()
            {
                return this->arr_ptr;
            }
            int parseToInt(int start_pos,int end_pos)
            {
                int number=0;
                bool is_positive=true;
                switch(this->getElement(start_pos))
                {
                case 45://-
                    is_positive=false;
                case 43://+
                    ++start_pos;
                    break;
                default:
                    if(charIsNumber(this->getElement(start_pos)))
                        break;
                    return 0;
                }
                int bit=0;
                for(;end_pos>=start_pos; --end_pos,++bit)
                {
                    number+=charParseToInt(this->getElement(end_pos))*powi(10,bit);
                }
                return is_positive?number:(-number);
            }

            int parseToInt(void)
            {
                return parseToInt(0,this->length-1);
            }

            int parseToInt_Hex(int start_pos,int end_pos)
            {
                int num=0;
                int bit=0;
                for(char ch=this->getElement(end_pos);end_pos>=start_pos;--end_pos,++bit,ch=this->getElement(end_pos))
                {
                    if(ch>64&&ch<71)//A-F
                        num+=(ch-55)*powi(16,bit);
                    else if(ch>96&&ch<103)//a-f
                        num+=(ch-87)*powi(16,bit);
                    else if(ch>47&&ch<58)//0-9
                        num+=(ch-48)*powi(16,bit);
                }
                return num;
            }

            int parseToInt_Hex(void)
            {
                return parseToInt_Hex(0,this->length-1);
            }

            static constexpr String<> toUpperCase(String<> str)
            {
                char chars[str.length];
                char ch;
                for(int pos=0;pos<str.length;++pos)
                {
                    ch=str.getElement(pos);
                    chars[pos]=ch>96&&ch<123?ch-32:ch;
                }
                return String<>(chars);
            }

            String<> toUpperCase(void)
            {
                return toUpperCase(*this);
            }

            int isNumber(int start_pos,int end_pos)
            {
                switch(this->getElement(start_pos))
                {
                case 43://+
                case 45://-
                    break;
                default:
                    if(charIsNumber(this->getElement(start_pos)))
                        break;
                    return false;
                }
                for(; start_pos<=end_pos; ++start_pos)
                {
                    if(!charIsNumber(this->getElement(start_pos)))
                        return false;
                }
                return true;
            }

            bool equals(String<> &str)
            {
                if(this->length!=str.length)return false;
                for(int pos=0;pos<this->length;++pos)
                    if(this->getElement(pos)!=str.getElement(pos))
                        return false;
                return true;
            }

            inline bool equals(String<> &&str)
            {
                if(this->length!=str.length)return false;
                for(int pos=0;pos<this->length;++pos)
                    if(this->getElement(pos)!=str.getElement(pos))
                        return false;
                return true;
            }

            bool operator== (String<> &str)
            {
                return equals(str);
            }
            String<> operator + (String<> &str)
            {
                Array<char> res(this->length+str.length);
                for(int pos=0; pos<this->length; ++pos)
                    *(res.arr_ptr+pos)=*(this->arr_ptr+pos);
                for(int pos=0; pos<str.length; ++pos)
                    *(res.arr_ptr+this->length+pos)=*(str.arr_ptr+pos);
                return String(res.arr_ptr,res.length);
            }
            String<> operator + (String<> &&str)
            {
                Array<char> res(this->length+str.length);
                for(int pos=0; pos<this->length; ++pos)
                    *(res.arr_ptr+pos)=*(this->arr_ptr+pos);
                for(int pos=0; pos<str.length; ++pos)
                    *(res.arr_ptr+this->length+pos)=*(str.arr_ptr+pos);
                return String(res.arr_ptr,res.length);
            }
            int isNumber(void)
            {
                return isNumber(0,this->length-1);
            }

            static String<> intParseToString_Hex_0x(int num)
            {
                char *str=new char[11]{'0','x','0','0','0','0','0','0','0','0','\0'};
                for(register int i=9;i>1;--i){
                    str[i]=intParseToChar_Hex(num%16);
                    num/=16;
                }
                return String<>(str,10);
            }

            static String<> intParseToString(int num)
            {
                DataBuffer<char> db(32);
                db<<'\0';
                for(;num>9;num/=10)
                    db<<intParseToChar_Hex(num%10);
                db<<intParseToChar_Hex(num);
                Array<char> str=db.toReservedArray();
                return String(str);
            }
            static inline int ifIsCharParseToInt(char ch)
            {
                if(charIsNumber(ch))
                    return ch-48;
                return -1;
            }
            static inline int charParseToInt(char ch)
            {
                return ch-48;
            }
            static inline bool charIsNumber(char ch)
            {
                return (ch>47&&ch<58);
            }
            static inline bool charIsNumber_Hex(char ch)
            {
                return (ch>47&&ch<58)||(ch>64&&ch<71)||(ch>96&&ch<103);
            }
            static inline int charParseToInt_Hex(char ch)
            {
                int v=-1;
                if(ch>47&&ch<58)v=ch-48;
                else if(ch>64&&ch<71)v=ch-55;
                else if(ch>96&&ch<103)v=ch-87;
                return v;
            }
            static inline int intParseToChar_Hex(int i)
            {
                char v='\0';
                if(i>-1&&i<10)v=(char)i+48;
                else if(i>9&&i<17)v=(char)i+55;
                return v;
            }
            static inline int powi(int *n,int *p)
            {
                if(p==0)return 1;
                int res=n;
                while(--p)res*=n;
                return res;
            }
            static inline char charToUpperCase(char ch)
            {
                return ch>96&&ch<123?ch-32:ch;
            }
        };
        template<bool delete_array_when_destruct=false>
        using String=struct String<delete_array_when_destruct>;

        class StringBuffer:public DataBuffer<char>
        {
            public:
            StringBuffer(int cap):DataBuffer<char>(cap){}
            inline String<false> toString(){
                int length=getLength();
                char *arr=new char[length];
                for(register int pos=0;pos<length;++pos)arr[pos]=*(head+pos);
                arr[length]='\0';
                return String<false>(arr,length);
            }

            StringBuffer & operator <<(const char *str){
                for(int pos=0;;++pos)
                {
                    if(*(str+pos)=='\0')break;
                    *(head+(++position))=*(str+pos);
                }
                return *this;
            }

            StringBuffer & operator <<(char &ch)
            {
                *(head+(++position))=ch;
                return *this;
            }

            StringBuffer & operator <<(char &&ch)
            {
                *(head+(++position))=ch;
                return *this;
            }

            StringBuffer & operator <<(String<> &str){
                for(int pos=0;pos<str.length;++pos)
                {
                    *(head+(++position))=str.getElement(pos);
                }
                return *this;
            }

            StringBuffer & operator <<(String<> &&str){
                for(int pos=0;pos<str.length;++pos)
                {
                    *(head+(++position))=str.getElement(pos);
                }
                return *this;
            }
        };
    }
}

#endif // UTILITIES_STRING
