#line 1 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.c"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.h"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_enum.h"




enum mk_hash_e
{
	#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_xmacro_def.h"
























#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_enum.h"
	
	mk_hash_e_crc32 , mk_hash_e_md2 , mk_hash_e_md4 , mk_hash_e_md5 , mk_hash_e_sha1 , mk_hash_e_sha2_224 , mk_hash_e_sha2_256 , mk_hash_e_sha2_384 , mk_hash_e_sha2_512 , mk_hash_e_sha2_512224 , mk_hash_e_sha2_512256 , mk_hash_e_sha3_224 , mk_hash_e_sha3_256 , mk_hash_e_sha3_384 , mk_hash_e_sha3_512
	
	#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_xmacro_undef.h"









#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_enum.h"
};






















#line 36 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_enum.h"
#line 6 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.h"

#line 1 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_jumbo.h"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_inline.h"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_setup.h"








#line 10 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_setup.h"






#line 17 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_setup.h"




#line 22 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_setup.h"

#line 24 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_setup.h"


#line 27 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_setup.h"
#line 6 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_inline.h"






#line 13 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_inline.h"


#line 16 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_inline.h"
#line 6 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_jumbo.h"




#line 11 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_jumbo.h"

#line 13 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_jumbo.h"


#line 16 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_jumbo.h"
#line 8 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.h"


typedef struct mk_hash_function_s { void* m_val; } mk_hash_function_h;


 mk_hash_function_h mk_hash_function_create(enum mk_hash_e type);
 int mk_hash_function_is_good(mk_hash_function_h hash_function);
 enum mk_hash_e mk_hash_function_get_type(mk_hash_function_h hash_function);
 void mk_hash_function_reinit(mk_hash_function_h hash_function);
 void mk_hash_function_append(mk_hash_function_h hash_function, void const* msg, int msg_len);
 void mk_hash_function_finish(mk_hash_function_h hash_function, void* digest);
 void mk_hash_function_destroy(mk_hash_function_h hash_function);


#line 23 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.h"
#line 2 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.c"

#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_all.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_crc32.h"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_id.h"



























#line 29 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_id.h"
#line 6 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_crc32.h"





#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_crc32.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_crc32.h"






#line 1 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_32.h"





#pragma warning(push)
#pragma warning(disable:4464) 
#line 9 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_32.h"


#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_32.h"
#pragma external_header(push)
#line 1 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\limits.h"







#pragma once


#pragma external_header(push)
#line 1 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"







#pragma once






















#line 32 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"

#line 34 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
#line 35 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"


    
#line 39 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"






    
    

#line 49 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
        
            
        

#line 54 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
    #line 55 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
#line 56 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"

#pragma external_header(push)
#line 1 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"













#pragma once







































































































































#line 151 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"



#line 155 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"





























#line 185 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"


#line 188 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"

#line 190 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"





#line 196 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"



#line 200 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"






#line 207 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"











#line 219 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"








#line 228 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"
#line 229 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"































































































































































































































































































































































































































































































#pragma region Input Buffer SAL 1 compatibility macros



























































































































































































































































































































































































































































































































































































































































































































































































#pragma endregion Input Buffer SAL 1 compatibility macros

















































































#line 1555 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"






























#line 1586 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"
























#line 1611 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"












#line 1624 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"






































#line 1663 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"















































































































#line 1775 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"






































































































#line 1878 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"








































































































































































#line 2047 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"





































































































#line 2149 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"
























































































































































































































#line 2366 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"
#line 2367 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"



































































































































































































































#line 2595 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

    
    
    
    

    
    

#line 2634 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"









































































































































































































































#line 2868 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"









#line 2878 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"



    
    


#line 2886 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"
#line 2887 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"






#line 2894 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"
#line 2895 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"






#line 2902 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"
#line 2903 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"











#line 2915 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"

































#line 2949 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"

























#pragma external_header(push)
#line 1 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\concurrencysal.h"


















#pragma once















































































































































































































































































#line 292 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\concurrencysal.h"



#line 296 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\concurrencysal.h"




























































































#line 389 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\concurrencysal.h"





#line 395 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\concurrencysal.h"
#pragma external_header(pop)
#line 2975 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\sal.h"
#pragma external_header(pop)
#line 58 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
#pragma external_header(push)
#line 1 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"










#pragma once



#pragma pack(push, 8 )



    


        
    #line 24 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"
#line 25 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"




    


        
    #line 34 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"
#line 35 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"



    
#line 40 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"




    
#line 46 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"

#pragma warning(push)
#pragma warning(disable: 4514 4820 )







#line 57 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"


    
    
        typedef unsigned __int64  uintptr_t;
    

#line 65 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"
#line 66 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"


    
    


        typedef char* va_list;
    #line 74 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"
#line 75 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"




    
#line 81 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"





#line 87 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"



#line 91 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"
    
    
#line 94 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"











#line 106 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"







#line 114 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"











#line 126 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"





#line 132 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"










#line 143 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"










#line 154 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"

    void __cdecl __va_start(va_list* , ...);

    
    



    

#line 165 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"




































#line 202 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"

    

#line 206 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vadefs.h"

#pragma warning(pop) 
#pragma pack(pop)
#pragma external_header(pop)
#line 59 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"

#pragma warning(push)
#pragma warning(disable: 4514 4820 )














#line 77 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"









#line 87 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"

    


    


#line 95 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"

__pragma(pack(push, 8))




    


        
    #line 106 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
#line 107 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
















    

#line 126 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"

#line 128 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
        
    #line 130 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
#line 131 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"


    

#line 136 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
        
    #line 138 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
#line 139 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"





#line 145 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
    
    
#line 148 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"




    
#line 154 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"








    


#line 166 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"



#line 170 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
    
#line 172 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"




    
#line 178 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"


    



      
    #line 186 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
#line 187 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"






    typedef unsigned __int64 size_t;
    typedef __int64          ptrdiff_t;
    typedef __int64          intptr_t;




#line 201 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"



#line 205 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"



#line 209 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
    typedef _Bool __vcrt_bool;
#line 211 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"



    
#line 216 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"


    
#line 220 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"


    
#line 224 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"



    
    typedef unsigned short wchar_t;
#line 230 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"


    


        
    #line 237 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
#line 238 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"


    


#line 244 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"



#line 248 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"










    
#line 260 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"



#line 264 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"








    
#line 274 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"


    

#line 279 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
        
    #line 281 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
#line 282 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"


    

#line 287 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
        
    #line 289 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
#line 290 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"


    

#line 295 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
        
    #line 297 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
#line 298 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"





#line 304 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"



#line 308 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"



    
        
    



#line 318 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
#line 319 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"



#line 323 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
    
#line 325 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"






#line 332 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"


    


        




    #line 343 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
#line 344 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"



#line 348 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"


    
        
    


#line 356 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
#line 357 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"


    void __cdecl __security_init_cookie(void);

    


#line 365 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"


#line 368 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
        void __cdecl __security_check_cookie( uintptr_t _StackCookie);
        __declspec(noreturn) void __cdecl __report_gsfailure( uintptr_t _StackCookie);
    #line 371 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
#line 372 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"

extern uintptr_t __security_cookie;


    
    
    
#line 380 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"

__pragma(pack(pop))

#pragma warning(pop) 

#line 386 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\vcruntime.h"
#pragma external_header(pop)
#line 12 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\limits.h"

#pragma warning(push)
#pragma warning(disable: 4514 4820 )

__pragma(pack(push, 8))







    
    



#line 30 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\limits.h"
































    
    
        
    

#line 68 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\limits.h"
#line 69 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\limits.h"





#line 75 "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include\\limits.h"

__pragma(pack(pop))

#pragma warning(pop) 
#pragma external_header(pop)
#line 2 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_32.h"




#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\base\\mk_uint_macro_base_int.h"




#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\base\\mk_uint_macro_base.h"















































#line 6 "C:\\dev\\repos\\mk_int\\src\\macro\\base\\mk_uint_macro_base_int.h"



#line 7 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_32.h"






#line 14 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_32.h"
#line 15 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_32.h"






#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact.h"














































#line 22 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_32.h"
#line 12 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_32.h"


#line 1 "C:\\dev\\repos\\mk_int\\src\\inl\\mk_uint.h"
#line 1 "C:\\dev\\repos\\mk_int\\src\\utils\\mk_jumbo.h"















#line 2 "C:\\dev\\repos\\mk_int\\src\\inl\\mk_uint.h"








struct mk_uint32_s
{
	unsigned int m_data;
};











#line 26 "C:\\dev\\repos\\mk_int\\src\\inl\\mk_uint.h"


 void mk_uint32_zero (struct mk_uint32_s * out);
 void mk_uint32_one (struct mk_uint32_s * out);
 void mk_uint32_from_int (struct mk_uint32_s * out, unsigned in);
 unsigned mk_uint32_to_int (struct mk_uint32_s const* x);
 void mk_uint32_from_long (struct mk_uint32_s * out, unsigned long in);
 unsigned long mk_uint32_to_long (struct mk_uint32_s const* x);
 void mk_uint32_from_sizet (struct mk_uint32_s * out, size_t in);
 size_t mk_uint32_to_sizet (struct mk_uint32_s const* x);
 void mk_uint32_from_buff_le (struct mk_uint32_s * out, void const* buff);
 void mk_uint32_to_buff_le (struct mk_uint32_s const* x, void* buff);
 void mk_uint32_from_buff_be (struct mk_uint32_s * out, void const* buff);
 void mk_uint32_to_buff_be (struct mk_uint32_s const* x, void* buff);

 int mk_uint32_is_zero (struct mk_uint32_s const* x);
 int mk_uint32_is_max (struct mk_uint32_s const* x);

 void mk_uint32_cmplmnt (struct mk_uint32_s * out, struct mk_uint32_s const* x);
 void mk_uint32_or (struct mk_uint32_s * out, struct mk_uint32_s const* a, struct mk_uint32_s const* b);
 void mk_uint32_and (struct mk_uint32_s * out, struct mk_uint32_s const* a, struct mk_uint32_s const* b);
 void mk_uint32_xor (struct mk_uint32_s * out, struct mk_uint32_s const* a, struct mk_uint32_s const* b);

 void mk_uint32_shl (struct mk_uint32_s * out, struct mk_uint32_s const* x, int n);
 void mk_uint32_shr (struct mk_uint32_s * out, struct mk_uint32_s const* x, int n);
 void mk_uint32_rotl (struct mk_uint32_s * out, struct mk_uint32_s const* x, int n);
 void mk_uint32_rotr (struct mk_uint32_s * out, struct mk_uint32_s const* x, int n);

 int mk_uint32_eq (struct mk_uint32_s const* a, struct mk_uint32_s const* b);
 int mk_uint32_neq (struct mk_uint32_s const* a, struct mk_uint32_s const* b);
 int mk_uint32_lt (struct mk_uint32_s const* a, struct mk_uint32_s const* b);
 int mk_uint32_le (struct mk_uint32_s const* a, struct mk_uint32_s const* b);
 int mk_uint32_gt (struct mk_uint32_s const* a, struct mk_uint32_s const* b);
 int mk_uint32_ge (struct mk_uint32_s const* a, struct mk_uint32_s const* b);

 void mk_uint32_inc (struct mk_uint32_s * x);
 void mk_uint32_dec (struct mk_uint32_s * x);

 void mk_uint32_add (struct mk_uint32_s * out, struct mk_uint32_s const* a, struct mk_uint32_s const* b);
 void mk_uint32_sub (struct mk_uint32_s * out, struct mk_uint32_s const* a, struct mk_uint32_s const* b);
 void mk_uint32_mul (struct mk_uint32_s * out, struct mk_uint32_s const* a, struct mk_uint32_s const* b);
 void mk_uint32_div (struct mk_uint32_s * out, struct mk_uint32_s const* a, struct mk_uint32_s const* b);
 void mk_uint32_mod (struct mk_uint32_s * out, struct mk_uint32_s const* a, struct mk_uint32_s const* b);



#line 15 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_32.h"


#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_undef.h"
#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\base\\mk_uint_macro_base_undef.h"















































#line 2 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_undef.h"




















































#line 18 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_32.h"



#pragma warning(pop)
#line 23 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_32.h"


#line 26 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_32.h"
#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_crc32.h"


struct mk_hash_base_hash_crc32_s
{
	struct mk_uint32_s m_state;
};


enum mk_hash_base_hash_crc32_block_len_e { mk_hash_base_hash_crc32_block_len = 1 };
enum mk_hash_base_hash_crc32_digest_len_e { mk_hash_base_hash_crc32_digest_len = 4 };
static char const mk_hash_base_hash_crc32_name[] = "CRC-32";
static int const mk_hash_base_hash_crc32_name_len = (int)sizeof(mk_hash_base_hash_crc32_name) - 1;


 void mk_hash_base_hash_crc32_init(struct mk_hash_base_hash_crc32_s* self);
 void mk_hash_base_hash_crc32_append_blocks(struct mk_hash_base_hash_crc32_s* self, int nblocks, void const* pblocks);
 void mk_hash_base_hash_crc32_finish(struct mk_hash_base_hash_crc32_s* self, void* block, int idx, void* digest);


#line 28 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_crc32.h"
#line 6 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"




























#line 35 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 2 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"











































#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"













struct mk_hash_hash_crc32_s
{
	struct mk_hash_base_hash_crc32_s m_base;
	int m_idx;
	unsigned char m_block[mk_hash_base_hash_crc32_block_len ];
};


 void mk_hash_hash_crc32_init (struct mk_hash_hash_crc32_s * self);
 void mk_hash_hash_crc32_append (struct mk_hash_hash_crc32_s * self, void const* msg, int msg_len);
 void mk_hash_hash_crc32_finish (struct mk_hash_hash_crc32_s * self, void* digest);













#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_undef.h"

#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_crc32.h"




#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_crc32.h"


#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_crc32.h"
#line 2 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_all.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_md2.h"










#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_md2.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"





#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_md2.h"







struct mk_hash_base_hash_md2_s
{
	unsigned char m_state[16];
	unsigned char m_checksum[16];
};


enum mk_hash_base_hash_md2_block_len_e { mk_hash_base_hash_md2_block_len = 16 };
enum mk_hash_base_hash_md2_digest_len_e { mk_hash_base_hash_md2_digest_len = 16 };
static char const mk_hash_base_hash_md2_name[] = "MD2";
static int const mk_hash_base_hash_md2_name_len = (int)sizeof(mk_hash_base_hash_md2_name) - 1;


 void mk_hash_base_hash_md2_init(struct mk_hash_base_hash_md2_s* self);
 void mk_hash_base_hash_md2_append_blocks(struct mk_hash_base_hash_md2_s* self, int nblocks, void const* pblocks);
 void mk_hash_base_hash_md2_finish(struct mk_hash_base_hash_md2_s* self, void* block, int idx, void* digest);


#line 27 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_md2.h"
#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"


























#line 35 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 2 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"






#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"




































#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"













struct mk_hash_hash_md2_s
{
	struct mk_hash_base_hash_md2_s m_base;
	int m_idx;
	unsigned char m_block[mk_hash_base_hash_md2_block_len ];
};


 void mk_hash_hash_md2_init (struct mk_hash_hash_md2_s * self);
 void mk_hash_hash_md2_append (struct mk_hash_hash_md2_s * self, void const* msg, int msg_len);
 void mk_hash_hash_md2_finish (struct mk_hash_hash_md2_s * self, void* digest);













#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_undef.h"

#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_md2.h"




#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_md2.h"


#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_md2.h"
#line 3 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_all.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_md4.h"










#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_md4.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"





#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 9 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_md4.h"







#line 1 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_64.h"





#pragma warning(push)
#pragma warning(disable:4464) 
#line 9 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_64.h"


#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_64.h"
#line 1 "C:\\dev\\repos\\mk_int\\src\\mk_uint_setup.h"


























#line 2 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_64.h"







#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\base\\mk_uint_macro_base_llong.h"




#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\base\\mk_uint_macro_base.h"















































#line 6 "C:\\dev\\repos\\mk_int\\src\\macro\\base\\mk_uint_macro_base_llong.h"



#line 10 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_64.h"


#line 13 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_64.h"






#line 20 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_64.h"
#line 21 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_64.h"






#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact.h"














































#line 28 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_64.h"
#line 12 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_64.h"


#line 1 "C:\\dev\\repos\\mk_int\\src\\inl\\mk_uint.h"
#line 1 "C:\\dev\\repos\\mk_int\\src\\utils\\mk_jumbo.h"















#line 2 "C:\\dev\\repos\\mk_int\\src\\inl\\mk_uint.h"








struct mk_uint64_s
{
	unsigned long long m_data;
};











#line 26 "C:\\dev\\repos\\mk_int\\src\\inl\\mk_uint.h"


 void mk_uint64_zero (struct mk_uint64_s * out);
 void mk_uint64_one (struct mk_uint64_s * out);
 void mk_uint64_from_int (struct mk_uint64_s * out, unsigned in);
 unsigned mk_uint64_to_int (struct mk_uint64_s const* x);
 void mk_uint64_from_long (struct mk_uint64_s * out, unsigned long in);
 unsigned long mk_uint64_to_long (struct mk_uint64_s const* x);
 void mk_uint64_from_sizet (struct mk_uint64_s * out, size_t in);
 size_t mk_uint64_to_sizet (struct mk_uint64_s const* x);
 void mk_uint64_from_buff_le (struct mk_uint64_s * out, void const* buff);
 void mk_uint64_to_buff_le (struct mk_uint64_s const* x, void* buff);
 void mk_uint64_from_buff_be (struct mk_uint64_s * out, void const* buff);
 void mk_uint64_to_buff_be (struct mk_uint64_s const* x, void* buff);

 int mk_uint64_is_zero (struct mk_uint64_s const* x);
 int mk_uint64_is_max (struct mk_uint64_s const* x);

 void mk_uint64_cmplmnt (struct mk_uint64_s * out, struct mk_uint64_s const* x);
 void mk_uint64_or (struct mk_uint64_s * out, struct mk_uint64_s const* a, struct mk_uint64_s const* b);
 void mk_uint64_and (struct mk_uint64_s * out, struct mk_uint64_s const* a, struct mk_uint64_s const* b);
 void mk_uint64_xor (struct mk_uint64_s * out, struct mk_uint64_s const* a, struct mk_uint64_s const* b);

 void mk_uint64_shl (struct mk_uint64_s * out, struct mk_uint64_s const* x, int n);
 void mk_uint64_shr (struct mk_uint64_s * out, struct mk_uint64_s const* x, int n);
 void mk_uint64_rotl (struct mk_uint64_s * out, struct mk_uint64_s const* x, int n);
 void mk_uint64_rotr (struct mk_uint64_s * out, struct mk_uint64_s const* x, int n);

 int mk_uint64_eq (struct mk_uint64_s const* a, struct mk_uint64_s const* b);
 int mk_uint64_neq (struct mk_uint64_s const* a, struct mk_uint64_s const* b);
 int mk_uint64_lt (struct mk_uint64_s const* a, struct mk_uint64_s const* b);
 int mk_uint64_le (struct mk_uint64_s const* a, struct mk_uint64_s const* b);
 int mk_uint64_gt (struct mk_uint64_s const* a, struct mk_uint64_s const* b);
 int mk_uint64_ge (struct mk_uint64_s const* a, struct mk_uint64_s const* b);

 void mk_uint64_inc (struct mk_uint64_s * x);
 void mk_uint64_dec (struct mk_uint64_s * x);

 void mk_uint64_add (struct mk_uint64_s * out, struct mk_uint64_s const* a, struct mk_uint64_s const* b);
 void mk_uint64_sub (struct mk_uint64_s * out, struct mk_uint64_s const* a, struct mk_uint64_s const* b);
 void mk_uint64_mul (struct mk_uint64_s * out, struct mk_uint64_s const* a, struct mk_uint64_s const* b);
 void mk_uint64_div (struct mk_uint64_s * out, struct mk_uint64_s const* a, struct mk_uint64_s const* b);
 void mk_uint64_mod (struct mk_uint64_s * out, struct mk_uint64_s const* a, struct mk_uint64_s const* b);



#line 15 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_64.h"


#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_undef.h"
#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\base\\mk_uint_macro_base_undef.h"















































#line 2 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_undef.h"




















































#line 18 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_64.h"



#pragma warning(pop)
#line 23 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_64.h"


#line 26 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_64.h"
#line 9 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_md4.h"


struct mk_hash_base_hash_md4_s
{
	struct mk_uint32_s m_state[4];
	struct mk_uint64_s m_len;
};


enum mk_hash_base_hash_md4_block_len_e { mk_hash_base_hash_md4_block_len = 64 };
enum mk_hash_base_hash_md4_digest_len_e { mk_hash_base_hash_md4_digest_len = 16 };
static char const mk_hash_base_hash_md4_name[] = "MD4";
static int const mk_hash_base_hash_md4_name_len = (int)sizeof(mk_hash_base_hash_md4_name) - 1;


 void mk_hash_base_hash_md4_init(struct mk_hash_base_hash_md4_s* self);
 void mk_hash_base_hash_md4_append_blocks(struct mk_hash_base_hash_md4_s* self, int nblocks, void const* pblocks);
 void mk_hash_base_hash_md4_finish(struct mk_hash_base_hash_md4_s* self, void* block, int idx, void* digest);


#line 30 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_md4.h"
#line 10 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
























#line 35 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 2 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"






#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 10 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"


































#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"













struct mk_hash_hash_md4_s
{
	struct mk_hash_base_hash_md4_s m_base;
	int m_idx;
	unsigned char m_block[mk_hash_base_hash_md4_block_len ];
};


 void mk_hash_hash_md4_init (struct mk_hash_hash_md4_s * self);
 void mk_hash_hash_md4_append (struct mk_hash_hash_md4_s * self, void const* msg, int msg_len);
 void mk_hash_hash_md4_finish (struct mk_hash_hash_md4_s * self, void* digest);













#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_undef.h"

#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_md4.h"




#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_md4.h"


#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_md4.h"
#line 4 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_all.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_md5.h"










#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_md5.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"





#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 9 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 11 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_md5.h"










struct mk_hash_base_hash_md5_s
{
	struct mk_uint32_s m_state[4];
	struct mk_uint64_s m_len;
};


enum mk_hash_base_hash_md5_block_len_e { mk_hash_base_hash_md5_block_len = 64 };
enum mk_hash_base_hash_md5_digest_len_e { mk_hash_base_hash_md5_digest_len = 16 };
static char const mk_hash_base_hash_md5_name[] = "MD5";
static int const mk_hash_base_hash_md5_name_len = (int)sizeof(mk_hash_base_hash_md5_name) - 1;


 void mk_hash_base_hash_md5_init(struct mk_hash_base_hash_md5_s* self);
 void mk_hash_base_hash_md5_append_blocks(struct mk_hash_base_hash_md5_s* self, int nblocks, void const* pblocks);
 void mk_hash_base_hash_md5_finish(struct mk_hash_base_hash_md5_s* self, void* block, int idx, void* digest);


#line 30 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_md5.h"
#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"






















#line 35 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 2 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"






#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 10 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
































#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"













struct mk_hash_hash_md5_s
{
	struct mk_hash_base_hash_md5_s m_base;
	int m_idx;
	unsigned char m_block[mk_hash_base_hash_md5_block_len ];
};


 void mk_hash_hash_md5_init (struct mk_hash_hash_md5_s * self);
 void mk_hash_hash_md5_append (struct mk_hash_hash_md5_s * self, void const* msg, int msg_len);
 void mk_hash_hash_md5_finish (struct mk_hash_hash_md5_s * self, void* digest);













#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_undef.h"

#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_md5.h"




#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_md5.h"


#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_md5.h"
#line 5 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_all.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha1.h"










#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha1.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"





#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 9 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 11 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha1.h"










struct mk_hash_base_hash_sha1_s
{
	struct mk_uint32_s m_state[5];
	struct mk_uint64_s m_len;
};


enum mk_hash_base_hash_sha1_block_len_e { mk_hash_base_hash_sha1_block_len = 64 };
enum mk_hash_base_hash_sha1_digest_len_e { mk_hash_base_hash_sha1_digest_len = 20 };
static char const mk_hash_base_hash_sha1_name[] = "SHA-1";
static int const mk_hash_base_hash_sha1_name_len = (int)sizeof(mk_hash_base_hash_sha1_name) - 1;


 void mk_hash_base_hash_sha1_init(struct mk_hash_base_hash_sha1_s* self);
 void mk_hash_base_hash_sha1_append_blocks(struct mk_hash_base_hash_sha1_s* self, int nblocks, void const* pblocks);
 void mk_hash_base_hash_sha1_finish(struct mk_hash_base_hash_sha1_s* self, void* block, int idx, void* digest);


#line 30 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha1.h"
#line 14 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"




















#line 35 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 2 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"






#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 10 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 14 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"






























#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"













struct mk_hash_hash_sha1_s
{
	struct mk_hash_base_hash_sha1_s m_base;
	int m_idx;
	unsigned char m_block[mk_hash_base_hash_sha1_block_len ];
};


 void mk_hash_hash_sha1_init (struct mk_hash_hash_sha1_s * self);
 void mk_hash_hash_sha1_append (struct mk_hash_hash_sha1_s * self, void const* msg, int msg_len);
 void mk_hash_hash_sha1_finish (struct mk_hash_hash_sha1_s * self, void* digest);













#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_undef.h"

#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha1.h"




#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha1.h"


#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha1.h"
#line 6 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_all.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_224.h"










#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_224.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"





#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 9 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 11 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 15 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha2_224.h"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\detail\\mk_hash_base_detail_sha2_256.h"










struct mk_hash_base_detail_sha2_256_s
{
	struct mk_uint32_s m_state[8];
	struct mk_uint64_s m_len;
};


 void mk_hash_base_detail_sha2_256_init(struct mk_hash_base_detail_sha2_256_s* hash_base_detail_sha2_256, struct mk_uint32_s const* iv);
 void mk_hash_base_detail_sha2_256_append_blocks(struct mk_hash_base_detail_sha2_256_s* hash_base_detail_sha2_256, int nblocks, void const* pblocks);
 void mk_hash_base_detail_sha2_256_finish(struct mk_hash_base_detail_sha2_256_s* hash_base_detail_sha2_256, void* block, int idx, void* digest);


#line 24 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\detail\\mk_hash_base_detail_sha2_256.h"
#line 6 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha2_224.h"




struct mk_hash_base_hash_sha2_224_s
{
	struct mk_hash_base_detail_sha2_256_s m_256;
};


enum mk_hash_base_hash_sha2_224_block_len_e { mk_hash_base_hash_sha2_224_block_len = 64 };
enum mk_hash_base_hash_sha2_224_digest_len_e { mk_hash_base_hash_sha2_224_digest_len = 28 };
static char const mk_hash_base_hash_sha2_224_name[] = "SHA-224";
static int const mk_hash_base_hash_sha2_224_name_len = (int)sizeof(mk_hash_base_hash_sha2_224_name) - 1;


 void mk_hash_base_hash_sha2_224_init(struct mk_hash_base_hash_sha2_224_s* self);
 void mk_hash_base_hash_sha2_224_append_blocks(struct mk_hash_base_hash_sha2_224_s* self, int nblocks, void const* pblocks);
 void mk_hash_base_hash_sha2_224_finish(struct mk_hash_base_hash_sha2_224_s* self, void* block, int idx, void* digest);


#line 28 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha2_224.h"
#line 16 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"


















#line 35 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 2 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"






#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 10 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 14 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 16 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"




























#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"













struct mk_hash_hash_sha2_224_s
{
	struct mk_hash_base_hash_sha2_224_s m_base;
	int m_idx;
	unsigned char m_block[mk_hash_base_hash_sha2_224_block_len ];
};


 void mk_hash_hash_sha2_224_init (struct mk_hash_hash_sha2_224_s * self);
 void mk_hash_hash_sha2_224_append (struct mk_hash_hash_sha2_224_s * self, void const* msg, int msg_len);
 void mk_hash_hash_sha2_224_finish (struct mk_hash_hash_sha2_224_s * self, void* digest);













#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_undef.h"

#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_224.h"




#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_224.h"


#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_224.h"
#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_all.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_256.h"










#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_256.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"





#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 9 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 11 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 15 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 17 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha2_256.h"









struct mk_hash_base_hash_sha2_256_s
{
	struct mk_hash_base_detail_sha2_256_s m_256;
};


enum mk_hash_base_hash_sha2_256_block_len_e { mk_hash_base_hash_sha2_256_block_len = 64 };
enum mk_hash_base_hash_sha2_256_digest_len_e { mk_hash_base_hash_sha2_256_digest_len = 32 };
static char const mk_hash_base_hash_sha2_256_name[] = "SHA-256";
static int const mk_hash_base_hash_sha2_256_name_len = (int)sizeof(mk_hash_base_hash_sha2_256_name) - 1;


 void mk_hash_base_hash_sha2_256_init(struct mk_hash_base_hash_sha2_256_s* self);
 void mk_hash_base_hash_sha2_256_append_blocks(struct mk_hash_base_hash_sha2_256_s* self, int nblocks, void const* pblocks);
 void mk_hash_base_hash_sha2_256_finish(struct mk_hash_base_hash_sha2_256_s* self, void* block, int idx, void* digest);


#line 28 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha2_256.h"
#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
















#line 35 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 2 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"






#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 10 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 14 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 16 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"


























#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"













struct mk_hash_hash_sha2_256_s
{
	struct mk_hash_base_hash_sha2_256_s m_base;
	int m_idx;
	unsigned char m_block[mk_hash_base_hash_sha2_256_block_len ];
};


 void mk_hash_hash_sha2_256_init (struct mk_hash_hash_sha2_256_s * self);
 void mk_hash_hash_sha2_256_append (struct mk_hash_hash_sha2_256_s * self, void const* msg, int msg_len);
 void mk_hash_hash_sha2_256_finish (struct mk_hash_hash_sha2_256_s * self, void* digest);













#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_undef.h"

#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_256.h"




#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_256.h"


#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_256.h"
#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_all.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_384.h"










#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_384.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"





#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 9 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 11 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 15 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 17 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 19 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha2_384.h"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\detail\\mk_hash_base_detail_sha2_512.h"







#line 1 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_128.h"





#pragma warning(push)
#pragma warning(disable:4464) 



#line 12 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_128.h"


#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_128.h"
#line 1 "C:\\dev\\repos\\mk_int\\src\\mk_uint_setup.h"


























#line 2 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_128.h"







#line 10 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_128.h"







#line 18 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_128.h"


#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\base\\mk_uint_macro_base_llong.h"




#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\base\\mk_uint_macro_base.h"















































#line 6 "C:\\dev\\repos\\mk_int\\src\\macro\\base\\mk_uint_macro_base_llong.h"



#line 21 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_128.h"


#line 24 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_128.h"






#line 31 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_128.h"
#line 32 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_128.h"
#line 33 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_128.h"






#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact.h"














































#line 40 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_128.h"




#line 45 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_128.h"
#line 15 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_128.h"


#line 1 "C:\\dev\\repos\\mk_int\\src\\inl\\mk_uint.h"
#line 1 "C:\\dev\\repos\\mk_int\\src\\utils\\mk_jumbo.h"















#line 2 "C:\\dev\\repos\\mk_int\\src\\inl\\mk_uint.h"














#line 17 "C:\\dev\\repos\\mk_int\\src\\inl\\mk_uint.h"


struct mk_uint128_s
{
	unsigned long long m_data[((128 + (64 - 1)) / 64) ];
};


#line 26 "C:\\dev\\repos\\mk_int\\src\\inl\\mk_uint.h"


 void mk_uint128_zero (struct mk_uint128_s * out);
 void mk_uint128_one (struct mk_uint128_s * out);
 void mk_uint128_from_int (struct mk_uint128_s * out, unsigned in);
 unsigned mk_uint128_to_int (struct mk_uint128_s const* x);
 void mk_uint128_from_long (struct mk_uint128_s * out, unsigned long in);
 unsigned long mk_uint128_to_long (struct mk_uint128_s const* x);
 void mk_uint128_from_sizet (struct mk_uint128_s * out, size_t in);
 size_t mk_uint128_to_sizet (struct mk_uint128_s const* x);
 void mk_uint128_from_buff_le (struct mk_uint128_s * out, void const* buff);
 void mk_uint128_to_buff_le (struct mk_uint128_s const* x, void* buff);
 void mk_uint128_from_buff_be (struct mk_uint128_s * out, void const* buff);
 void mk_uint128_to_buff_be (struct mk_uint128_s const* x, void* buff);

 int mk_uint128_is_zero (struct mk_uint128_s const* x);
 int mk_uint128_is_max (struct mk_uint128_s const* x);

 void mk_uint128_cmplmnt (struct mk_uint128_s * out, struct mk_uint128_s const* x);
 void mk_uint128_or (struct mk_uint128_s * out, struct mk_uint128_s const* a, struct mk_uint128_s const* b);
 void mk_uint128_and (struct mk_uint128_s * out, struct mk_uint128_s const* a, struct mk_uint128_s const* b);
 void mk_uint128_xor (struct mk_uint128_s * out, struct mk_uint128_s const* a, struct mk_uint128_s const* b);

 void mk_uint128_shl (struct mk_uint128_s * out, struct mk_uint128_s const* x, int n);
 void mk_uint128_shr (struct mk_uint128_s * out, struct mk_uint128_s const* x, int n);
 void mk_uint128_rotl (struct mk_uint128_s * out, struct mk_uint128_s const* x, int n);
 void mk_uint128_rotr (struct mk_uint128_s * out, struct mk_uint128_s const* x, int n);

 int mk_uint128_eq (struct mk_uint128_s const* a, struct mk_uint128_s const* b);
 int mk_uint128_neq (struct mk_uint128_s const* a, struct mk_uint128_s const* b);
 int mk_uint128_lt (struct mk_uint128_s const* a, struct mk_uint128_s const* b);
 int mk_uint128_le (struct mk_uint128_s const* a, struct mk_uint128_s const* b);
 int mk_uint128_gt (struct mk_uint128_s const* a, struct mk_uint128_s const* b);
 int mk_uint128_ge (struct mk_uint128_s const* a, struct mk_uint128_s const* b);

 void mk_uint128_inc (struct mk_uint128_s * x);
 void mk_uint128_dec (struct mk_uint128_s * x);

 void mk_uint128_add (struct mk_uint128_s * out, struct mk_uint128_s const* a, struct mk_uint128_s const* b);
 void mk_uint128_sub (struct mk_uint128_s * out, struct mk_uint128_s const* a, struct mk_uint128_s const* b);
 void mk_uint128_mul (struct mk_uint128_s * out, struct mk_uint128_s const* a, struct mk_uint128_s const* b);
 void mk_uint128_div (struct mk_uint128_s * out, struct mk_uint128_s const* a, struct mk_uint128_s const* b);
 void mk_uint128_mod (struct mk_uint128_s * out, struct mk_uint128_s const* a, struct mk_uint128_s const* b);



#line 18 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_128.h"


#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_undef.h"
#line 1 "C:\\dev\\repos\\mk_int\\src\\macro\\base\\mk_uint_macro_base_undef.h"















































#line 2 "C:\\dev\\repos\\mk_int\\src\\macro\\exact\\mk_uint_macro_exact_undef.h"




















































#line 21 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_128.h"



#pragma warning(pop)


#line 28 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_128.h"


#line 31 "C:\\dev\\repos\\mk_int\\src\\exact\\mk_uint_128.h"
#line 9 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\detail\\mk_hash_base_detail_sha2_512.h"


struct mk_hash_base_detail_sha2_512_s
{
	struct mk_uint64_s m_state[8];
	struct mk_uint128_s m_len;
};


 void mk_hash_base_detail_sha2_512_init(struct mk_hash_base_detail_sha2_512_s* hash_base_detail_sha2_512, struct mk_uint64_s const* iv);
 void mk_hash_base_detail_sha2_512_append_blocks(struct mk_hash_base_detail_sha2_512_s* hash_base_detail_sha2_512, int nblocks, void const* pblocks);
 void mk_hash_base_detail_sha2_512_finish(struct mk_hash_base_detail_sha2_512_s* hash_base_detail_sha2_512, void* block, int idx, void* digest);


#line 24 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\detail\\mk_hash_base_detail_sha2_512.h"
#line 6 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha2_384.h"




struct mk_hash_base_hash_sha2_384_s
{
	struct mk_hash_base_detail_sha2_512_s m_512;
};


enum mk_hash_base_hash_sha2_384_block_len_e { mk_hash_base_hash_sha2_384_block_len = 128 };
enum mk_hash_base_hash_sha2_384_digest_len_e { mk_hash_base_hash_sha2_384_digest_len = 48 };
static char const mk_hash_base_hash_sha2_384_name[] = "SHA-384";
static int const mk_hash_base_hash_sha2_384_name_len = (int)sizeof(mk_hash_base_hash_sha2_384_name) - 1;


 void mk_hash_base_hash_sha2_384_init(struct mk_hash_base_hash_sha2_384_s* self);
 void mk_hash_base_hash_sha2_384_append_blocks(struct mk_hash_base_hash_sha2_384_s* self, int nblocks, void const* pblocks);
 void mk_hash_base_hash_sha2_384_finish(struct mk_hash_base_hash_sha2_384_s* self, void* block, int idx, void* digest);


#line 28 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha2_384.h"
#line 20 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"














#line 35 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 2 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"






#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 10 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 14 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 16 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 20 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
























#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"













struct mk_hash_hash_sha2_384_s
{
	struct mk_hash_base_hash_sha2_384_s m_base;
	int m_idx;
	unsigned char m_block[mk_hash_base_hash_sha2_384_block_len ];
};


 void mk_hash_hash_sha2_384_init (struct mk_hash_hash_sha2_384_s * self);
 void mk_hash_hash_sha2_384_append (struct mk_hash_hash_sha2_384_s * self, void const* msg, int msg_len);
 void mk_hash_hash_sha2_384_finish (struct mk_hash_hash_sha2_384_s * self, void* digest);













#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_undef.h"

#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_384.h"




#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_384.h"


#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_384.h"
#line 9 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_all.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_512.h"










#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_512.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"





#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 9 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 11 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 15 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 17 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 19 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha2_512.h"









struct mk_hash_base_hash_sha2_512_s
{
	struct mk_hash_base_detail_sha2_512_s m_512;
};


enum mk_hash_base_hash_sha2_512_block_len_e { mk_hash_base_hash_sha2_512_block_len = 128 };
enum mk_hash_base_hash_sha2_512_digest_len_e { mk_hash_base_hash_sha2_512_digest_len = 64 };
static char const mk_hash_base_hash_sha2_512_name[] = "SHA-512";
static int const mk_hash_base_hash_sha2_512_name_len = (int)sizeof(mk_hash_base_hash_sha2_512_name) - 1;


 void mk_hash_base_hash_sha2_512_init(struct mk_hash_base_hash_sha2_512_s* self);
 void mk_hash_base_hash_sha2_512_append_blocks(struct mk_hash_base_hash_sha2_512_s* self, int nblocks, void const* pblocks);
 void mk_hash_base_hash_sha2_512_finish(struct mk_hash_base_hash_sha2_512_s* self, void* block, int idx, void* digest);


#line 28 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha2_512.h"
#line 22 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"












#line 35 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 2 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"






#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 10 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 14 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 16 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 20 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 22 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"






















#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"













struct mk_hash_hash_sha2_512_s
{
	struct mk_hash_base_hash_sha2_512_s m_base;
	int m_idx;
	unsigned char m_block[mk_hash_base_hash_sha2_512_block_len ];
};


 void mk_hash_hash_sha2_512_init (struct mk_hash_hash_sha2_512_s * self);
 void mk_hash_hash_sha2_512_append (struct mk_hash_hash_sha2_512_s * self, void const* msg, int msg_len);
 void mk_hash_hash_sha2_512_finish (struct mk_hash_hash_sha2_512_s * self, void* digest);













#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_undef.h"

#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_512.h"




#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_512.h"


#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_512.h"
#line 10 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_all.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_512224.h"










#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_512224.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"





#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 9 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 11 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 15 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 17 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 19 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 23 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha2_512224.h"









struct mk_hash_base_hash_sha2_512224_s
{
	struct mk_hash_base_detail_sha2_512_s m_512;
};


enum mk_hash_base_hash_sha2_512224_block_len_e { mk_hash_base_hash_sha2_512224_block_len = 128 };
enum mk_hash_base_hash_sha2_512224_digest_len_e { mk_hash_base_hash_sha2_512224_digest_len = 28 };
static char const mk_hash_base_hash_sha2_512224_name[] = "SHA-512/224";
static int const mk_hash_base_hash_sha2_512224_name_len = (int)sizeof(mk_hash_base_hash_sha2_512224_name) - 1;


 void mk_hash_base_hash_sha2_512224_init(struct mk_hash_base_hash_sha2_512224_s* self);
 void mk_hash_base_hash_sha2_512224_append_blocks(struct mk_hash_base_hash_sha2_512224_s* self, int nblocks, void const* pblocks);
 void mk_hash_base_hash_sha2_512224_finish(struct mk_hash_base_hash_sha2_512224_s* self, void* block, int idx, void* digest);


#line 28 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha2_512224.h"
#line 24 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"










#line 35 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 2 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"






#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 10 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 14 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 16 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 20 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 22 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 24 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"




















#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"













struct mk_hash_hash_sha2_512224_s
{
	struct mk_hash_base_hash_sha2_512224_s m_base;
	int m_idx;
	unsigned char m_block[mk_hash_base_hash_sha2_512224_block_len ];
};


 void mk_hash_hash_sha2_512224_init (struct mk_hash_hash_sha2_512224_s * self);
 void mk_hash_hash_sha2_512224_append (struct mk_hash_hash_sha2_512224_s * self, void const* msg, int msg_len);
 void mk_hash_hash_sha2_512224_finish (struct mk_hash_hash_sha2_512224_s * self, void* digest);













#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_undef.h"

#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_512224.h"




#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_512224.h"


#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_512224.h"
#line 11 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_all.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_512256.h"










#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_512256.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"





#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 9 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 11 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 15 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 17 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 19 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 23 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 25 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha2_512256.h"









struct mk_hash_base_hash_sha2_512256_s
{
	struct mk_hash_base_detail_sha2_512_s m_512;
};


enum mk_hash_base_hash_sha2_512256_block_len_e { mk_hash_base_hash_sha2_512256_block_len = 128 };
enum mk_hash_base_hash_sha2_512256_digest_len_e { mk_hash_base_hash_sha2_512256_digest_len = 32 };
static char const mk_hash_base_hash_sha2_512256_name[] = "SHA-512/256";
static int const mk_hash_base_hash_sha2_512256_name_len = (int)sizeof(mk_hash_base_hash_sha2_512256_name) - 1;


 void mk_hash_base_hash_sha2_512256_init(struct mk_hash_base_hash_sha2_512256_s* self);
 void mk_hash_base_hash_sha2_512256_append_blocks(struct mk_hash_base_hash_sha2_512256_s* self, int nblocks, void const* pblocks);
 void mk_hash_base_hash_sha2_512256_finish(struct mk_hash_base_hash_sha2_512256_s* self, void* block, int idx, void* digest);


#line 28 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha2_512256.h"
#line 26 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"








#line 35 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 2 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"






#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 10 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 14 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 16 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 20 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 22 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 24 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 26 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"


















#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"













struct mk_hash_hash_sha2_512256_s
{
	struct mk_hash_base_hash_sha2_512256_s m_base;
	int m_idx;
	unsigned char m_block[mk_hash_base_hash_sha2_512256_block_len ];
};


 void mk_hash_hash_sha2_512256_init (struct mk_hash_hash_sha2_512256_s * self);
 void mk_hash_hash_sha2_512256_append (struct mk_hash_hash_sha2_512256_s * self, void const* msg, int msg_len);
 void mk_hash_hash_sha2_512256_finish (struct mk_hash_hash_sha2_512256_s * self, void* digest);













#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_undef.h"

#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_512256.h"




#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_512256.h"


#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha2_512256.h"
#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_all.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_224.h"










#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_224.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"





#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 9 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 11 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 15 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 17 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 19 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 23 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 25 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 27 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha3_224.h"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\detail\\mk_hash_base_detail_sha3.h"









struct mk_hash_base_detail_sha3_s
{
	struct mk_uint64_s m_state[25];
};


enum mk_hash_base_detail_sha3_domain_e
{
	mk_hash_base_detail_sha3_domain_sha3,
	mk_hash_base_detail_sha3_domain_shake,
	mk_hash_base_detail_sha3_domain_rawshake
};


 void mk_hash_base_detail_sha3_init(struct mk_hash_base_detail_sha3_s* hash_base_detail_sha3);
 void mk_hash_base_detail_sha3_append_blocks(struct mk_hash_base_detail_sha3_s* hash_base_detail_sha3, int block_len, int nblocks, void const* pblocks);
 void mk_hash_base_detail_sha3_finish(struct mk_hash_base_detail_sha3_s* hash_base_detail_sha3, int block_len, void* block, int idx, enum mk_hash_base_detail_sha3_domain_e domain, int digest_len, void* digest);


#line 30 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\detail\\mk_hash_base_detail_sha3.h"
#line 6 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha3_224.h"




struct mk_hash_base_hash_sha3_224_s
{
	struct mk_hash_base_detail_sha3_s m_sha3;
};


enum mk_hash_base_hash_sha3_224_block_len_e { mk_hash_base_hash_sha3_224_block_len = 144 };
enum mk_hash_base_hash_sha3_224_digest_len_e { mk_hash_base_hash_sha3_224_digest_len = 28 };
static char const mk_hash_base_hash_sha3_224_name[] = "SHA3-224";
static int const mk_hash_base_hash_sha3_224_name_len = (int)sizeof(mk_hash_base_hash_sha3_224_name) - 1;


 void mk_hash_base_hash_sha3_224_init(struct mk_hash_base_hash_sha3_224_s* self);
 void mk_hash_base_hash_sha3_224_append_blocks(struct mk_hash_base_hash_sha3_224_s* self, int nblocks, void const* pblocks);
 void mk_hash_base_hash_sha3_224_finish(struct mk_hash_base_hash_sha3_224_s* self, void* block, int idx, void* digest);


#line 28 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha3_224.h"
#line 28 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"






#line 35 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 2 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"






#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 10 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 14 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 16 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 20 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 22 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 24 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 26 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 28 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
















#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"













struct mk_hash_hash_sha3_224_s
{
	struct mk_hash_base_hash_sha3_224_s m_base;
	int m_idx;
	unsigned char m_block[mk_hash_base_hash_sha3_224_block_len ];
};


 void mk_hash_hash_sha3_224_init (struct mk_hash_hash_sha3_224_s * self);
 void mk_hash_hash_sha3_224_append (struct mk_hash_hash_sha3_224_s * self, void const* msg, int msg_len);
 void mk_hash_hash_sha3_224_finish (struct mk_hash_hash_sha3_224_s * self, void* digest);













#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_undef.h"

#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_224.h"




#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_224.h"


#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_224.h"
#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_all.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_256.h"










#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_256.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"





#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 9 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 11 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 15 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 17 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 19 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 23 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 25 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 27 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 29 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha3_256.h"









struct mk_hash_base_hash_sha3_256_s
{
	struct mk_hash_base_detail_sha3_s m_sha3;
};


enum mk_hash_base_hash_sha3_256_block_len_e { mk_hash_base_hash_sha3_256_block_len = 136 };
enum mk_hash_base_hash_sha3_256_digest_len_e { mk_hash_base_hash_sha3_256_digest_len = 32 };
static char const mk_hash_base_hash_sha3_256_name[] = "SHA3-256";
static int const mk_hash_base_hash_sha3_256_name_len = (int)sizeof(mk_hash_base_hash_sha3_256_name) - 1;


 void mk_hash_base_hash_sha3_256_init(struct mk_hash_base_hash_sha3_256_s* self);
 void mk_hash_base_hash_sha3_256_append_blocks(struct mk_hash_base_hash_sha3_256_s* self, int nblocks, void const* pblocks);
 void mk_hash_base_hash_sha3_256_finish(struct mk_hash_base_hash_sha3_256_s* self, void* block, int idx, void* digest);


#line 28 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha3_256.h"
#line 30 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"




#line 35 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 2 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"






#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 10 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 14 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 16 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 20 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 22 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 24 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 26 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 28 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 30 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"














#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"













struct mk_hash_hash_sha3_256_s
{
	struct mk_hash_base_hash_sha3_256_s m_base;
	int m_idx;
	unsigned char m_block[mk_hash_base_hash_sha3_256_block_len ];
};


 void mk_hash_hash_sha3_256_init (struct mk_hash_hash_sha3_256_s * self);
 void mk_hash_hash_sha3_256_append (struct mk_hash_hash_sha3_256_s * self, void const* msg, int msg_len);
 void mk_hash_hash_sha3_256_finish (struct mk_hash_hash_sha3_256_s * self, void* digest);













#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_undef.h"

#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_256.h"




#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_256.h"


#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_256.h"
#line 14 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_all.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_384.h"










#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_384.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"





#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 9 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 11 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 15 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 17 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 19 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 23 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 25 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 27 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 29 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 31 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha3_384.h"









struct mk_hash_base_hash_sha3_384_s
{
	struct mk_hash_base_detail_sha3_s m_sha3;
};


enum mk_hash_base_hash_sha3_384_block_len_e { mk_hash_base_hash_sha3_384_block_len = 104 };
enum mk_hash_base_hash_sha3_384_digest_len_e { mk_hash_base_hash_sha3_384_digest_len = 48 };
static char const mk_hash_base_hash_sha3_384_name[] = "SHA3-384";
static int const mk_hash_base_hash_sha3_384_name_len = (int)sizeof(mk_hash_base_hash_sha3_384_name) - 1;


 void mk_hash_base_hash_sha3_384_init(struct mk_hash_base_hash_sha3_384_s* self);
 void mk_hash_base_hash_sha3_384_append_blocks(struct mk_hash_base_hash_sha3_384_s* self, int nblocks, void const* pblocks);
 void mk_hash_base_hash_sha3_384_finish(struct mk_hash_base_hash_sha3_384_s* self, void* block, int idx, void* digest);


#line 28 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha3_384.h"
#line 32 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"


#line 35 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 2 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"






#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 10 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 14 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 16 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 20 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 22 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 24 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 26 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 28 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 30 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 32 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"












#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"













struct mk_hash_hash_sha3_384_s
{
	struct mk_hash_base_hash_sha3_384_s m_base;
	int m_idx;
	unsigned char m_block[mk_hash_base_hash_sha3_384_block_len ];
};


 void mk_hash_hash_sha3_384_init (struct mk_hash_hash_sha3_384_s * self);
 void mk_hash_hash_sha3_384_append (struct mk_hash_hash_sha3_384_s * self, void const* msg, int msg_len);
 void mk_hash_hash_sha3_384_finish (struct mk_hash_hash_sha3_384_s * self, void* digest);













#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_undef.h"

#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_384.h"




#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_384.h"


#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_384.h"
#line 15 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_all.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_512.h"










#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_512.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"





#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 9 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 11 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 15 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 17 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 19 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 23 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 25 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 27 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 29 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 31 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"

#line 33 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha3_512.h"









struct mk_hash_base_hash_sha3_512_s
{
	struct mk_hash_base_detail_sha3_s m_sha3;
};


enum mk_hash_base_hash_sha3_512_block_len_e { mk_hash_base_hash_sha3_512_block_len = 72 };
enum mk_hash_base_hash_sha3_512_digest_len_e { mk_hash_base_hash_sha3_512_digest_len = 64 };
static char const mk_hash_base_hash_sha3_512_name[] = "SHA3-512";
static int const mk_hash_base_hash_sha3_512_name_len = (int)sizeof(mk_hash_base_hash_sha3_512_name) - 1;


 void mk_hash_base_hash_sha3_512_init(struct mk_hash_base_hash_sha3_512_s* self);
 void mk_hash_base_hash_sha3_512_append_blocks(struct mk_hash_base_hash_sha3_512_s* self, int nblocks, void const* pblocks);
 void mk_hash_base_hash_sha3_512_finish(struct mk_hash_base_hash_sha3_512_s* self, void* block, int idx, void* digest);


#line 28 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\hash\\mk_hash_base_hash_sha3_512.h"
#line 34 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 35 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_hash.h"
#line 2 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"






#line 8 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 10 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 12 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 14 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 16 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 20 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 22 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 24 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 26 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 28 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 30 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 32 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"

#line 34 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"










#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_def.h"
#line 7 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"













struct mk_hash_hash_sha3_512_s
{
	struct mk_hash_base_hash_sha3_512_s m_base;
	int m_idx;
	unsigned char m_block[mk_hash_base_hash_sha3_512_block_len ];
};


 void mk_hash_hash_sha3_512_init (struct mk_hash_hash_sha3_512_s * self);
 void mk_hash_hash_sha3_512_append (struct mk_hash_hash_sha3_512_s * self, void const* msg, int msg_len);
 void mk_hash_hash_sha3_512_finish (struct mk_hash_hash_sha3_512_s * self, void* digest);













#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_alg_name_undef.h"

#line 45 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash.h.inl"
#line 13 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_512.h"




#line 18 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_512.h"


#line 21 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_sha3_512.h"
#line 16 "C:\\dev\\repos\\mk_crypto\\src\\hash\\hash\\mk_hash_hash_all.h"
#line 4 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.c"

#line 1 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_assert.h"













#line 15 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_assert.h"











#line 27 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_assert.h"


#line 30 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_assert.h"
#line 6 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.c"
#line 1 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_clobber.h"







 void mk_clobber(void* arg);


#line 12 "C:\\dev\\repos\\mk_crypto\\src\\utils\\mk_clobber.h"
#line 7 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.c"


#pragma external_header(push)
#line 1 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stddef.h"







#pragma once



#pragma external_header(push)
#line 1 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"







#pragma once









    

















        
    #line 38 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 39 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


    
#line 43 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


    
        
    

#line 50 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 51 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"

















    


        
    #line 73 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 74 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"



    
#line 79 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"














    
#line 95 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


    











        
    #line 111 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 112 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


    


        
    #line 119 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 120 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"

#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )


__pragma(pack(push, 8))







    

#line 136 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
        
    

#line 140 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 141 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"




    
#line 147 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


    

#line 152 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
        
    

#line 156 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 157 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"



#line 161 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
    
#line 163 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


    


#line 169 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"





#line 175 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
    
#line 177 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"



    


#line 184 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"



#line 188 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
    
#line 190 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"









    
#line 201 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"













    


        
    #line 219 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 220 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"



#line 224 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
    
#line 226 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"



#line 230 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
    
#line 232 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"



#line 236 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
    
#line 238 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


    


        
    #line 245 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 246 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"























#line 270 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"



#line 274 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
    typedef _Bool __crt_bool;
#line 276 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"














    
        


            
        #line 296 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
    #line 297 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 298 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"



















    

#line 320 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
        
    #line 322 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 323 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"



#line 327 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


    
#line 331 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


 






  

#line 343 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
   
  #line 345 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
 #line 346 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 347 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


 
   
 

#line 354 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 355 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
















__declspec(dllimport) void __cdecl _invalid_parameter_noinfo(void);
__declspec(dllimport) __declspec(noreturn) void __cdecl _invalid_parameter_noinfo_noreturn(void);

__declspec(noreturn)
__declspec(dllimport) void __cdecl _invoke_watson(
     wchar_t const* _Expression,
     wchar_t const* _FunctionName,
     wchar_t const* _FileName,
           unsigned int _LineNo,
           uintptr_t _Reserved);


    



        
        
        
        
        
        
        
        
        
        
        
        

    #line 401 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 402 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"












    


#line 419 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"



#line 423 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


    


        


    #line 432 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 433 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"









    






        
    #line 451 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 452 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


    


        
    #line 459 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 460 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"



#line 464 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"













#line 478 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"















#line 494 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"





    
#line 501 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"



#line 505 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


    

#line 510 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 511 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


    


        


            
        #line 521 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
    #line 522 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 523 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"



#line 527 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"





#line 533 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


    


        



    #line 543 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 544 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


    
        
    



#line 553 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"

    
        
        
        
    



#line 563 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"

    
        
              
        

#line 570 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
    



#line 575 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"

    
        
    



#line 583 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"

    
        
    



#line 591 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 592 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


    
#line 596 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"








typedef int                           errno_t;
typedef unsigned short                wint_t;
typedef unsigned short                wctype_t;
typedef long                          __time32_t;
typedef __int64                       __time64_t;

typedef struct __crt_locale_data_public
{
      unsigned short const* _locale_pctype;
     int _locale_mb_cur_max;
               unsigned int _locale_lc_codepage;
} __crt_locale_data_public;

typedef struct __crt_locale_pointers
{
    struct __crt_locale_data*    locinfo;
    struct __crt_multibyte_data* mbcinfo;
} __crt_locale_pointers;

typedef __crt_locale_pointers* _locale_t;

typedef struct _Mbstatet
{ 
    unsigned long _Wchar;
    unsigned short _Byte, _State;
} _Mbstatet;

typedef _Mbstatet mbstate_t;



#line 636 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"



#line 640 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


    


        typedef __time64_t time_t;
    #line 647 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 648 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"



    
#line 653 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"


    typedef size_t rsize_t;
#line 657 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"










    















































































































































#line 812 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"

        
        
        
        
        
        
        
        
        
        
        
        

    #line 827 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 828 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"












































































    













































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































#line 1879 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"

        
        
        
        

        

            


            


            


            


            


            


            


            


            



            



            


            


            


            


            


            


            


            


            


            


            



            



            



            


            



            




            

            




            

            




            

            




            

            




            

            




            

            




            

            




            

        











































#line 2069 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
    #line 2070 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"
#line 2071 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h"

__pragma(pack(pop))


#pragma warning(pop) 
#pragma external_header(pop)
#line 13 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stddef.h"

#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )


__pragma(pack(push, 8))
















    __declspec(dllimport) int* __cdecl _errno(void);
    

    __declspec(dllimport) errno_t __cdecl _set_errno( int _Value);
    __declspec(dllimport) errno_t __cdecl _get_errno( int* _Value);

#line 42 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stddef.h"




    


        
    #line 51 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stddef.h"


#line 54 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stddef.h"

__declspec(dllimport) extern unsigned long  __cdecl __threadid(void);

__declspec(dllimport) extern uintptr_t __cdecl __threadhandle(void);



__pragma(pack(pop))

#pragma warning(pop) 
#line 65 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stddef.h"
#pragma external_header(pop)
#line 10 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.c"
#pragma external_header(push)
#line 1 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"







#pragma once




#pragma external_header(push)
#line 1 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt_malloc.h"








#pragma once



#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )


__pragma(pack(push, 8))





































#line 56 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt_malloc.h"

  
__declspec(dllimport) __declspec(allocator) __declspec(restrict)
void* __cdecl _calloc_base(
     size_t _Count,
     size_t _Size
    );

  
__declspec(dllimport)  __declspec(allocator) __declspec(restrict) 
void* __cdecl calloc(
     __declspec(guard(overflow)) size_t _Count,
     __declspec(guard(overflow)) size_t _Size
    );


__declspec(dllimport) int __cdecl _callnewh(
     size_t _Size
    );

  
__declspec(dllimport) __declspec(allocator) 
void* __cdecl _expand(
               void*  _Block,
     __declspec(guard(overflow)) size_t _Size
    );

__declspec(dllimport)
void __cdecl _free_base(
      void* _Block
    );

__declspec(dllimport) 
void __cdecl free(
      void* _Block
    );

  
__declspec(dllimport) __declspec(allocator) __declspec(restrict)
void* __cdecl _malloc_base(
     size_t _Size
    );

  
__declspec(dllimport) __declspec(allocator)  __declspec(restrict) 
void* __cdecl malloc(
     __declspec(guard(overflow)) size_t _Size
    );


__declspec(dllimport)
size_t __cdecl _msize_base(
     void* _Block
    )  ;


__declspec(dllimport) 
size_t __cdecl _msize(
     void* _Block
    );

   
__declspec(dllimport) __declspec(allocator) __declspec(restrict)
void* __cdecl _realloc_base(
       void*  _Block,
                                size_t _Size
    );

   
__declspec(dllimport) __declspec(allocator) __declspec(restrict) 
void* __cdecl realloc(
      void*  _Block,
     __declspec(guard(overflow))        size_t _Size
    );

   
__declspec(dllimport) __declspec(allocator) __declspec(restrict)
void* __cdecl _recalloc_base(
      void*  _Block,
                               size_t _Count,
                               size_t _Size
    );

   
__declspec(dllimport) __declspec(allocator) __declspec(restrict)
void* __cdecl _recalloc(
      void*  _Block,
     __declspec(guard(overflow))        size_t _Count,
     __declspec(guard(overflow))        size_t _Size
    );

__declspec(dllimport)
void __cdecl _aligned_free(
      void* _Block
    );

  
__declspec(dllimport) __declspec(allocator) __declspec(restrict)
void* __cdecl _aligned_malloc(
     __declspec(guard(overflow)) size_t _Size,
                        size_t _Alignment
    );

  
__declspec(dllimport) __declspec(allocator) __declspec(restrict)
void* __cdecl _aligned_offset_malloc(
     __declspec(guard(overflow)) size_t _Size,
                        size_t _Alignment,
                        size_t _Offset
    );


__declspec(dllimport)
size_t __cdecl _aligned_msize(
     void*  _Block,
              size_t _Alignment,
              size_t _Offset
    );

   
__declspec(dllimport) __declspec(allocator) __declspec(restrict)
void* __cdecl _aligned_offset_realloc(
      void*  _Block,
     __declspec(guard(overflow))        size_t _Size,
                               size_t _Alignment,
                               size_t _Offset
    );

   
__declspec(dllimport) __declspec(allocator) __declspec(restrict)
void* __cdecl _aligned_offset_recalloc(
      void*  _Block,
     __declspec(guard(overflow))        size_t _Count,
     __declspec(guard(overflow))        size_t _Size,
                               size_t _Alignment,
                               size_t _Offset
    );

   
__declspec(dllimport) __declspec(allocator) __declspec(restrict)
void* __cdecl _aligned_realloc(
      void*  _Block,
     __declspec(guard(overflow))        size_t _Size,
                               size_t _Alignment
    );

   
__declspec(dllimport) __declspec(allocator) __declspec(restrict)
void* __cdecl _aligned_recalloc(
      void*  _Block,
     __declspec(guard(overflow))        size_t _Count,
     __declspec(guard(overflow))        size_t _Size,
                               size_t _Alignment
    );


















#line 229 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt_malloc.h"



__pragma(pack(pop))

#pragma warning(pop) 
#pragma external_header(pop)
#line 14 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"
#pragma external_header(push)
#line 1 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt_search.h"










#pragma once




#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )


__pragma(pack(push, 8))


    typedef int (__cdecl* _CoreCrtSecureSearchSortCompareFunction)(void*, void const*, void const*);
    typedef int (__cdecl* _CoreCrtNonSecureSearchSortCompareFunction)(void const*, void const*);




    
    __declspec(dllimport) void* __cdecl bsearch_s(
                                                       void const* _Key,
         void const* _Base,
                                                       rsize_t     _NumOfElements,
                                                       rsize_t     _SizeOfElements,
                           _CoreCrtSecureSearchSortCompareFunction _CompareFunction,
                                                   void*       _Context
        );

    __declspec(dllimport) void __cdecl qsort_s(
         void*   _Base,
                                                            rsize_t _NumOfElements,
                                                            rsize_t _SizeOfElements,
                            _CoreCrtSecureSearchSortCompareFunction _CompareFunction,
                                                        void*   _Context
        );

#line 48 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt_search.h"




__declspec(dllimport) void* __cdecl bsearch(
                                                   void const* _Key,
     void const* _Base,
                                                   size_t      _NumOfElements,
                                                   size_t      _SizeOfElements,
                    _CoreCrtNonSecureSearchSortCompareFunction _CompareFunction
    );

__declspec(dllimport) void __cdecl qsort(
     void*  _Base,
                                                        size_t _NumOfElements,
                                                        size_t _SizeOfElements,
                    _CoreCrtNonSecureSearchSortCompareFunction _CompareFunction
    );


__declspec(dllimport) void* __cdecl _lfind_s(
                                                      void const*   _Key,
     void const*   _Base,
                                                   unsigned int* _NumOfElements,
                                                      size_t        _SizeOfElements,
                            _CoreCrtSecureSearchSortCompareFunction _CompareFunction,
                                                      void*         _Context
    );


__declspec(dllimport) void* __cdecl _lfind(
                                                      void const*   _Key,
     void const*   _Base,
                                                   unsigned int* _NumOfElements,
                                                      unsigned int  _SizeOfElements,
                         _CoreCrtNonSecureSearchSortCompareFunction _CompareFunction
    );


__declspec(dllimport) void* __cdecl _lsearch_s(
                                                            void const*   _Key,
     void*         _Base,
                                                         unsigned int* _NumOfElements,
                                                            size_t        _SizeOfElements,
                                  _CoreCrtSecureSearchSortCompareFunction _CompareFunction,
                                                            void*         _Context
    );


__declspec(dllimport) void* __cdecl _lsearch(
                                                            void const*   _Key,
     void*         _Base,
                                                         unsigned int* _NumOfElements,
                                                            unsigned int  _SizeOfElements,
                               _CoreCrtNonSecureSearchSortCompareFunction _CompareFunction
    );




















































































#line 189 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt_search.h"





     __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_lfind" ". See online help for details."))
    __declspec(dllimport) void* __cdecl lfind(
                                                          void const*   _Key,
         void const*   _Base,
                                                       unsigned int* _NumOfElements,
                                                          unsigned int  _SizeOfElements,
                             _CoreCrtNonSecureSearchSortCompareFunction _CompareFunction
        );

     __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_lsearch" ". See online help for details."))
    __declspec(dllimport) void* __cdecl lsearch(
                                                               void const*   _Key,
         void*         _Base,
                                                            unsigned int* _NumOfElements,
                                                               unsigned int  _SizeOfElements,
                                  _CoreCrtNonSecureSearchSortCompareFunction _CompareFunction
        );

#line 213 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt_search.h"



__pragma(pack(pop))

#pragma warning(pop) 
#pragma external_header(pop)
#line 15 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"
#pragma external_header(push)
#line 1 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt_wstdlib.h"








#pragma once



#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )


__pragma(pack(push, 8))


































    
    
    __declspec(dllimport) errno_t __cdecl _itow_s(
                                 int      _Value,
         wchar_t* _Buffer,
                                 size_t   _BufferCount,
                                 int      _Radix
        );

    






    __declspec(deprecated("This function or variable may be unsafe. Consider using " "_itow_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) __declspec(dllimport) wchar_t* __cdecl _itow(int _Value, wchar_t *_Buffer, int _Radix);






    
    
    __declspec(dllimport) errno_t __cdecl _ltow_s(
                                 long     _Value,
         wchar_t* _Buffer,
                                 size_t   _BufferCount,
                                 int      _Radix
        );

    






    __declspec(deprecated("This function or variable may be unsafe. Consider using " "_ltow_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) __declspec(dllimport) wchar_t* __cdecl _ltow(long _Value, wchar_t *_Buffer, int _Radix);






    
    __declspec(dllimport) errno_t __cdecl _ultow_s(
                                 unsigned long _Value,
         wchar_t*      _Buffer,
                                 size_t        _BufferCount,
                                 int           _Radix
        );

    






    __declspec(deprecated("This function or variable may be unsafe. Consider using " "_ultow_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) __declspec(dllimport) wchar_t* __cdecl _ultow(unsigned long _Value, wchar_t *_Buffer, int _Radix);






    
    __declspec(dllimport) double __cdecl wcstod(
                           wchar_t const* _String,
          wchar_t**      _EndPtr
        );

    
    __declspec(dllimport) double __cdecl _wcstod_l(
                           wchar_t const* _String,
          wchar_t**      _EndPtr,
                         _locale_t      _Locale
        );

    
    __declspec(dllimport) long __cdecl wcstol(
                           wchar_t const* _String,
          wchar_t**      _EndPtr,
                             int            _Radix
        );

    
    __declspec(dllimport) long __cdecl _wcstol_l(
                           wchar_t const* _String,
          wchar_t**      _EndPtr,
                             int            _Radix,
                         _locale_t      _Locale
        );

    
    __declspec(dllimport) long long __cdecl wcstoll(
                           wchar_t const* _String,
          wchar_t**      _EndPtr,
                             int            _Radix
        );

    
    __declspec(dllimport) long long __cdecl _wcstoll_l(
                           wchar_t const* _String,
          wchar_t**      _EndPtr,
                             int            _Radix,
                         _locale_t      _Locale
        );

    
    __declspec(dllimport) unsigned long __cdecl wcstoul(
                           wchar_t const* _String,
          wchar_t**      _EndPtr,
                             int            _Radix
        );

    
    __declspec(dllimport) unsigned long __cdecl _wcstoul_l(
                           wchar_t const* _String,
          wchar_t**      _EndPtr,
                             int            _Radix,
                         _locale_t      _Locale
        );

    
    __declspec(dllimport) unsigned long long __cdecl wcstoull(
                           wchar_t const* _String,
          wchar_t**      _EndPtr,
                             int            _Radix
        );

    
    __declspec(dllimport) unsigned long long __cdecl _wcstoull_l(
                           wchar_t const* _String,
          wchar_t**      _EndPtr,
                             int            _Radix,
                         _locale_t      _Locale
        );

    
    __declspec(dllimport) long double __cdecl wcstold(
                           wchar_t const* _String,
          wchar_t**      _EndPtr
        );

    
    __declspec(dllimport) long double __cdecl _wcstold_l(
                           wchar_t const* _String,
          wchar_t**      _EndPtr,
                         _locale_t      _Locale
        );

    
    __declspec(dllimport) float __cdecl wcstof(
                           wchar_t const* _String,
          wchar_t**      _EndPtr
        );

    
    __declspec(dllimport) float __cdecl _wcstof_l(
                           wchar_t const* _String,
          wchar_t**      _EndPtr,
                         _locale_t      _Locale
        );

    
    __declspec(dllimport) double __cdecl _wtof(
         wchar_t const* _String
        );

    
    __declspec(dllimport) double __cdecl _wtof_l(
           wchar_t const* _String,
         _locale_t      _Locale
        );

    
    __declspec(dllimport) int __cdecl _wtoi(
         wchar_t const* _String
        );

    
    __declspec(dllimport) int __cdecl _wtoi_l(
           wchar_t const* _String,
         _locale_t      _Locale
        );

    
    __declspec(dllimport) long __cdecl _wtol(
         wchar_t const* _String
        );

    
    __declspec(dllimport) long __cdecl _wtol_l(
           wchar_t const* _String,
         _locale_t      _Locale
        );

    
    __declspec(dllimport) long long __cdecl _wtoll(
         wchar_t const* _String
        );

    
    __declspec(dllimport) long long __cdecl _wtoll_l(
           wchar_t const* _String,
         _locale_t      _Locale
        );

    
    __declspec(dllimport) errno_t __cdecl _i64tow_s(
                                 __int64  _Value,
         wchar_t* _Buffer,
                                 size_t   _BufferCount,
                                 int      _Radix
        );

    __declspec(deprecated("This function or variable may be unsafe. Consider using " "_i64tow_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
    __declspec(dllimport) wchar_t* __cdecl _i64tow(
                           __int64  _Value,
          wchar_t* _Buffer,
                           int      _Radix
        );

    
    __declspec(dllimport) errno_t __cdecl _ui64tow_s(
                                 unsigned __int64 _Value,
         wchar_t*         _Buffer,
                                 size_t           _BufferCount,
                                 int              _Radix
        );

    __declspec(deprecated("This function or variable may be unsafe. Consider using " "_ui64tow_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
    __declspec(dllimport) wchar_t* __cdecl _ui64tow(
                           unsigned __int64 _Value,
          wchar_t*         _Buffer,
                           int              _Radix
        );

    
    __declspec(dllimport) __int64 __cdecl _wtoi64(
         wchar_t const* _String
        );

    
    __declspec(dllimport) __int64 __cdecl _wtoi64_l(
           wchar_t const* _String,
         _locale_t      _Locale
        );

    
    __declspec(dllimport) __int64 __cdecl _wcstoi64(
                           wchar_t const* _String,
          wchar_t**      _EndPtr,
                             int            _Radix
        );

    
    __declspec(dllimport) __int64 __cdecl _wcstoi64_l(
                           wchar_t const* _String,
          wchar_t**      _EndPtr,
                             int            _Radix,
                         _locale_t      _Locale
        );

    
    __declspec(dllimport) unsigned __int64 __cdecl _wcstoui64(
                           wchar_t const* _String,
          wchar_t**      _EndPtr,
                             int            _Radix
        );

    
    __declspec(dllimport) unsigned __int64 __cdecl _wcstoui64_l(
                           wchar_t const* _String,
          wchar_t**      _EndPtr,
                             int            _Radix,
                         _locale_t      _Locale
        );

    
    

    
    
    __declspec(dllimport) __declspec(allocator) wchar_t* __cdecl _wfullpath(
         wchar_t*       _Buffer,
                                   wchar_t const* _Path,
                                     size_t         _BufferCount
        );

    

    
    __declspec(dllimport) errno_t __cdecl _wmakepath_s(
         wchar_t*       _Buffer,
                                 size_t         _BufferCount,
                           wchar_t const* _Drive,
                           wchar_t const* _Dir,
                           wchar_t const* _Filename,
                           wchar_t const* _Ext
        );

    








__declspec(deprecated("This function or variable may be unsafe. Consider using " "_wmakepath_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) __declspec(dllimport) void __cdecl _wmakepath( wchar_t *_Buffer, wchar_t const* _Drive, wchar_t const* _Dir, wchar_t const* _Filename, wchar_t const* _Ext);








    __declspec(dllimport) void __cdecl _wperror(
         wchar_t const* _ErrorMessage
        );

    __declspec(deprecated("This function or variable may be unsafe. Consider using " "_wsplitpath_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
    __declspec(dllimport) void __cdecl _wsplitpath(
                           wchar_t const* _FullPath,
          wchar_t*       _Drive,
          wchar_t*       _Dir,
          wchar_t*       _Filename,
          wchar_t*       _Ext
        );

    __declspec(dllimport) errno_t __cdecl _wsplitpath_s(
                                     wchar_t const* _FullPath,
            wchar_t*       _Drive,
                                       size_t         _DriveCount,
              wchar_t*       _Dir,
                                       size_t         _DirCount,
         wchar_t*       _Filename,
                                       size_t         _FilenameCount,
              wchar_t*       _Ext,
                                       size_t         _ExtCount
        );

    




        
        

        
        __declspec(dllimport) errno_t __cdecl _wdupenv_s(
              wchar_t**      _Buffer,
                                                                               size_t*        _BufferCount,
                                                                                  wchar_t const* _VarName
            );

        

         __declspec(deprecated("This function or variable may be unsafe. Consider using " "_wdupenv_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
        __declspec(dllimport) wchar_t* __cdecl _wgetenv(
             wchar_t const* _VarName
            );

        
        
        __declspec(dllimport) errno_t __cdecl _wgetenv_s(
                                        size_t*        _RequiredCount,
             wchar_t*       _Buffer,
                                         size_t         _BufferCount,
                                       wchar_t const* _VarName
            );

        







        
        __declspec(dllimport) int __cdecl _wputenv(
             wchar_t const* _EnvString
            );

        
        __declspec(dllimport) errno_t __cdecl _wputenv_s(
             wchar_t const* _Name,
             wchar_t const* _Value
            );

        __declspec(dllimport) errno_t __cdecl _wsearchenv_s(
                                   wchar_t const* _Filename,
                                   wchar_t const* _VarName,
             wchar_t*       _Buffer,
                                     size_t         _BufferCount
            );

        






        __declspec(deprecated("This function or variable may be unsafe. Consider using " "_wsearchenv_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) __declspec(dllimport) void __cdecl _wsearchenv(wchar_t const* _Filename, wchar_t const* _VarName, wchar_t *_ResultPath);






        __declspec(dllimport) int __cdecl _wsystem(
             wchar_t const* _Command
            );

#line 476 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt_wstdlib.h"



__pragma(pack(pop))

#pragma warning(pop) 
#pragma external_header(pop)
#line 16 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"


#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )


__pragma(pack(push, 8))




    
#line 29 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"









__declspec(dllimport) void __cdecl _swab(
      char* _Buf1,
      char* _Buf2,
                                                                 int   _SizeInBytes
    );













    __declspec(dllimport) __declspec(noreturn) void __cdecl exit( int _Code);
    __declspec(dllimport) __declspec(noreturn) void __cdecl _exit( int _Code);
    __declspec(dllimport) __declspec(noreturn) void __cdecl _Exit( int _Code);
    __declspec(dllimport) __declspec(noreturn) void __cdecl quick_exit( int _Code);
    __declspec(dllimport) __declspec(noreturn) void __cdecl abort(void);
#line 62 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"





__declspec(dllimport) unsigned int __cdecl _set_abort_behavior(
     unsigned int _Flags,
     unsigned int _Mask
    );




    

    typedef int (__cdecl * _onexit_t)(void);
    


#line 82 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"


    
    
#line 87 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"

























































    int       __cdecl atexit(void (__cdecl*)(void));
    _onexit_t __cdecl _onexit( _onexit_t _Func);
#line 147 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"

int __cdecl at_quick_exit(void (__cdecl*)(void));









    
    typedef void (__cdecl* _purecall_handler)(void);

    
    typedef void (__cdecl* _invalid_parameter_handler)(
        wchar_t const*,
        wchar_t const*,
        wchar_t const*,
        unsigned int,
        uintptr_t
        );

    
     _purecall_handler __cdecl _set_purecall_handler(
         _purecall_handler _Handler
        );

     _purecall_handler __cdecl _get_purecall_handler(void);

    
    __declspec(dllimport) _invalid_parameter_handler __cdecl _set_invalid_parameter_handler(
         _invalid_parameter_handler _Handler
        );

    __declspec(dllimport) _invalid_parameter_handler __cdecl _get_invalid_parameter_handler(void);

    __declspec(dllimport) _invalid_parameter_handler __cdecl _set_thread_local_invalid_parameter_handler(
         _invalid_parameter_handler _Handler
        );

    __declspec(dllimport) _invalid_parameter_handler __cdecl _get_thread_local_invalid_parameter_handler(void);
#line 190 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"












#line 203 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"









 __declspec(dllimport) int __cdecl _set_error_mode( int _Mode);




    __declspec(dllimport) int* __cdecl _errno(void);
    

    __declspec(dllimport) errno_t __cdecl _set_errno( int _Value);
    __declspec(dllimport) errno_t __cdecl _get_errno( int* _Value);

    __declspec(dllimport) unsigned long* __cdecl __doserrno(void);
    

    __declspec(dllimport) errno_t __cdecl _set_doserrno( unsigned long _Value);
    __declspec(dllimport) errno_t __cdecl _get_doserrno( unsigned long * _Value);

    
    __declspec(dllimport) __declspec(deprecated("This function or variable may be unsafe. Consider using " "strerror" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) char** __cdecl __sys_errlist(void);
    

    __declspec(dllimport) __declspec(deprecated("This function or variable may be unsafe. Consider using " "strerror" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) int * __cdecl __sys_nerr(void);
    

    __declspec(dllimport) void __cdecl perror( char const* _ErrMsg);
#line 238 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"




__declspec(deprecated("This function or variable may be unsafe. Consider using " "_get_pgmptr" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) __declspec(dllimport) char**    __cdecl __p__pgmptr (void);
__declspec(deprecated("This function or variable may be unsafe. Consider using " "_get_wpgmptr" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) __declspec(dllimport) wchar_t** __cdecl __p__wpgmptr(void);
__declspec(deprecated("This function or variable may be unsafe. Consider using " "_get_fmode" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) __declspec(dllimport) int*      __cdecl __p__fmode  (void);








    
    
    
#line 257 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"


__declspec(dllimport) errno_t __cdecl _get_pgmptr ( char**    _Value);


__declspec(dllimport) errno_t __cdecl _get_wpgmptr( wchar_t** _Value);

__declspec(dllimport) errno_t __cdecl _set_fmode  (              int       _Mode );

__declspec(dllimport) errno_t __cdecl _get_fmode  (             int*      _PMode);








typedef struct _div_t
{
    int quot;
    int rem;
} div_t;

typedef struct _ldiv_t
{
    long quot;
    long rem;
} ldiv_t;

typedef struct _lldiv_t
{
    long long quot;
    long long rem;
} lldiv_t;

 int       __cdecl abs   ( int       _Number);
 long      __cdecl labs  ( long      _Number);
 long long __cdecl llabs ( long long _Number);
 __int64   __cdecl _abs64( __int64   _Number);

 unsigned short   __cdecl _byteswap_ushort( unsigned short   _Number);
 unsigned long    __cdecl _byteswap_ulong ( unsigned long    _Number);
 unsigned __int64 __cdecl _byteswap_uint64( unsigned __int64 _Number);

 __declspec(dllimport) div_t   __cdecl div  ( int       _Numerator,  int       _Denominator);
 __declspec(dllimport) ldiv_t  __cdecl ldiv ( long      _Numerator,  long      _Denominator);
 __declspec(dllimport) lldiv_t __cdecl lldiv( long long _Numerator,  long long _Denominator);



#pragma warning(push)
#pragma warning(disable: 6540)

unsigned int __cdecl _rotl(
     unsigned int _Value,
     int          _Shift
    );


unsigned long __cdecl _lrotl(
     unsigned long _Value,
     int           _Shift
    );

unsigned __int64 __cdecl _rotl64(
     unsigned __int64 _Value,
     int              _Shift
    );

unsigned int __cdecl _rotr(
     unsigned int _Value,
     int          _Shift
    );


unsigned long __cdecl _lrotr(
     unsigned long _Value,
     int           _Shift
    );

unsigned __int64 __cdecl _rotr64(
     unsigned __int64 _Value,
     int              _Shift
    );

#pragma warning(pop)






__declspec(dllimport) void __cdecl srand( unsigned int _Seed);

 __declspec(dllimport) int __cdecl rand(void);



#line 357 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"





































    #pragma pack(push, 4)
    typedef struct
    {
        unsigned char ld[10];
    } _LDOUBLE;
    #pragma pack(pop)

    











#line 414 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"

typedef struct
{
    double x;
} _CRT_DOUBLE;

typedef struct
{
    float f;
} _CRT_FLOAT;





typedef struct
{
    long double x;
} _LONGDOUBLE;



#pragma pack(push, 4)
typedef struct
{
    unsigned char ld12[12];
} _LDBL12;
#pragma pack(pop)








                    __declspec(dllimport) double    __cdecl atof   ( char const* _String);
  __declspec(dllimport) int       __cdecl atoi   ( char const* _String);
                    __declspec(dllimport) long      __cdecl atol   ( char const* _String);
                    __declspec(dllimport) long long __cdecl atoll  ( char const* _String);
                    __declspec(dllimport) __int64   __cdecl _atoi64( char const* _String);

 __declspec(dllimport) double    __cdecl _atof_l  ( char const* _String,  _locale_t _Locale);
 __declspec(dllimport) int       __cdecl _atoi_l  ( char const* _String,  _locale_t _Locale);
 __declspec(dllimport) long      __cdecl _atol_l  ( char const* _String,  _locale_t _Locale);
 __declspec(dllimport) long long __cdecl _atoll_l ( char const* _String,  _locale_t _Locale);
 __declspec(dllimport) __int64   __cdecl _atoi64_l( char const* _String,  _locale_t _Locale);

 __declspec(dllimport) int __cdecl _atoflt ( _CRT_FLOAT*  _Result,  char const* _String);
 __declspec(dllimport) int __cdecl _atodbl ( _CRT_DOUBLE* _Result,  char*       _String);
 __declspec(dllimport) int __cdecl _atoldbl( _LDOUBLE*    _Result,  char*       _String);


__declspec(dllimport) int __cdecl _atoflt_l(
        _CRT_FLOAT* _Result,
       char const* _String,
     _locale_t   _Locale
    );


__declspec(dllimport) int __cdecl _atodbl_l(
        _CRT_DOUBLE* _Result,
       char*        _String,
     _locale_t    _Locale
    );



__declspec(dllimport) int __cdecl _atoldbl_l(
        _LDOUBLE* _Result,
       char*     _String,
     _locale_t _Locale
    );


__declspec(dllimport) float __cdecl strtof(
                       char const* _String,
      char**      _EndPtr
    );


__declspec(dllimport) float __cdecl _strtof_l(
                       char const* _String,
      char**      _EndPtr,
                     _locale_t   _Locale
    );


__declspec(dllimport) double __cdecl strtod(
                       char const* _String,
      char**      _EndPtr
    );


__declspec(dllimport) double __cdecl _strtod_l(
                       char const* _String,
      char**      _EndPtr,
                     _locale_t   _Locale
    );


__declspec(dllimport) long double __cdecl strtold(
                       char const* _String,
      char**      _EndPtr
    );


__declspec(dllimport) long double __cdecl _strtold_l(
                       char const* _String,
      char**      _EndPtr,
                     _locale_t   _Locale
    );


__declspec(dllimport) long __cdecl strtol(
                       char const* _String,
      char**      _EndPtr,
                         int         _Radix
    );


__declspec(dllimport) long __cdecl _strtol_l(
                       char const* _String,
      char**      _EndPtr,
                         int         _Radix,
                     _locale_t   _Locale
    );


__declspec(dllimport) long long __cdecl strtoll(
                       char const* _String,
      char**      _EndPtr,
                         int         _Radix
    );


__declspec(dllimport) long long __cdecl _strtoll_l(
                       char const* _String,
      char**      _EndPtr,
                         int         _Radix,
                     _locale_t   _Locale
    );


__declspec(dllimport) unsigned long __cdecl strtoul(
                       char const* _String,
      char**      _EndPtr,
                         int         _Radix
    );


__declspec(dllimport) unsigned long __cdecl _strtoul_l(
                       char const* _String,
      char**      _EndPtr,
                         int         _Radix,
                     _locale_t   _Locale
    );


__declspec(dllimport) unsigned long long __cdecl strtoull(
                       char const* _String,
      char**      _EndPtr,
                         int         _Radix
    );


__declspec(dllimport) unsigned long long __cdecl _strtoull_l(
                       char const* _String,
      char**      _EndPtr,
                         int         _Radix,
                     _locale_t   _Locale
    );


__declspec(dllimport) __int64 __cdecl _strtoi64(
                       char const* _String,
      char**      _EndPtr,
                         int         _Radix
    );


__declspec(dllimport) __int64 __cdecl _strtoi64_l(
                       char const* _String,
      char**      _EndPtr,
                         int         _Radix,
                     _locale_t   _Locale
    );


__declspec(dllimport) unsigned __int64 __cdecl _strtoui64(
                       char const* _String,
      char**      _EndPtr,
                         int         _Radix
    );


__declspec(dllimport) unsigned __int64 __cdecl _strtoui64_l(
                       char const* _String,
      char**      _EndPtr,
                         int         _Radix,
                     _locale_t   _Locale
    );










__declspec(dllimport) errno_t __cdecl _itoa_s(
                             int    _Value,
     char*  _Buffer,
                             size_t _BufferCount,
                             int    _Radix
    );









__declspec(deprecated("This function or variable may be unsafe. Consider using " "_itoa_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) __declspec(dllimport) char* __cdecl _itoa(int _Value, char *_Buffer, int _Radix);








__declspec(dllimport) errno_t __cdecl _ltoa_s(
                             long   _Value,
     char*  _Buffer,
                             size_t _BufferCount,
                             int    _Radix
    );








__declspec(deprecated("This function or variable may be unsafe. Consider using " "_ltoa_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) __declspec(dllimport) char* __cdecl _ltoa(long _Value, char *_Buffer, int _Radix);








__declspec(dllimport) errno_t __cdecl _ultoa_s(
                             unsigned long _Value,
     char*         _Buffer,
                             size_t        _BufferCount,
                             int           _Radix
    );








__declspec(deprecated("This function or variable may be unsafe. Consider using " "_ultoa_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) __declspec(dllimport) char* __cdecl _ultoa(unsigned long _Value, char *_Buffer, int _Radix);








__declspec(dllimport) errno_t __cdecl _i64toa_s(
                             __int64 _Value,
     char*   _Buffer,
                             size_t  _BufferCount,
                             int     _Radix
    );


__declspec(deprecated("This function or variable may be unsafe. Consider using " "_i64toa_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
__declspec(dllimport) char* __cdecl _i64toa(
                       __int64 _Value,
      char*   _Buffer,
                       int     _Radix
    );



__declspec(dllimport) errno_t __cdecl _ui64toa_s(
                             unsigned __int64 _Value,
     char*            _Buffer,
                             size_t           _BufferCount,
                             int              _Radix
    );

__declspec(deprecated("This function or variable may be unsafe. Consider using " "_ui64toa_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
__declspec(dllimport) char* __cdecl _ui64toa(
                       unsigned __int64 _Value,
      char*            _Buffer,
                       int              _Radix
    );















__declspec(dllimport) errno_t __cdecl _ecvt_s(
     char* _Buffer,
      size_t                       _BufferCount,
      double                       _Value,
      int                          _DigitCount,
     int*                         _PtDec,
     int*                         _PtSign
    );










 __declspec(deprecated("This function or variable may be unsafe. Consider using " "_ecvt_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
__declspec(dllimport) char* __cdecl _ecvt(
      double _Value,
      int    _DigitCount,
     int*   _PtDec,
     int*   _PtSign
    );



__declspec(dllimport) errno_t __cdecl _fcvt_s(
     char*  _Buffer,
                             size_t _BufferCount,
                             double _Value,
                             int    _FractionalDigitCount,
                            int*   _PtDec,
                            int*   _PtSign
    );












 __declspec(deprecated("This function or variable may be unsafe. Consider using " "_fcvt_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
__declspec(dllimport) char* __cdecl _fcvt(
      double _Value,
      int    _FractionalDigitCount,
     int*   _PtDec,
     int*   _PtSign
    );


__declspec(dllimport) errno_t __cdecl _gcvt_s(
     char*  _Buffer,
                             size_t _BufferCount,
                             double _Value,
                             int    _DigitCount
    );









__declspec(deprecated("This function or variable may be unsafe. Consider using " "_gcvt_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
__declspec(dllimport) char* __cdecl _gcvt(
                       double _Value,
                       int    _DigitCount,
      char*  _Buffer
    );











    

#line 833 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"
        
    #line 835 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"

    


        
    #line 841 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"

    
    __declspec(dllimport) int __cdecl ___mb_cur_max_func(void);

    
    __declspec(dllimport) int __cdecl ___mb_cur_max_l_func(_locale_t _Locale);
#line 848 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"




__declspec(dllimport) int __cdecl mblen(
      char const* _Ch,
                                            size_t      _MaxCount
    );


__declspec(dllimport) int __cdecl _mblen_l(
      char const* _Ch,
                                            size_t      _MaxCount,
                                        _locale_t   _Locale
    );



__declspec(dllimport) size_t __cdecl _mbstrlen(
     char const* _String
    );



__declspec(dllimport) size_t __cdecl _mbstrlen_l(
       char const* _String,
     _locale_t   _Locale
    );



__declspec(dllimport) size_t __cdecl _mbstrnlen(
     char const* _String,
       size_t      _MaxCount
    );



__declspec(dllimport) size_t __cdecl _mbstrnlen_l(
       char const* _String,
         size_t      _MaxCount,
     _locale_t   _Locale
    );


__declspec(dllimport) int __cdecl mbtowc(
                    wchar_t*    _DstCh,
     char const* _SrcCh,
                                     size_t      _SrcSizeInBytes
    );


__declspec(dllimport) int __cdecl _mbtowc_l(
                    wchar_t*    _DstCh,
     char const* _SrcCh,
                                     size_t      _SrcSizeInBytes,
                                 _locale_t   _Locale
    );


__declspec(dllimport) errno_t __cdecl mbstowcs_s(
                                                     size_t*     _PtNumOfCharConverted,
     wchar_t*    _DstBuf,
                                                          size_t      _SizeInWords,
                                    char const* _SrcBuf,
                                                          size_t      _MaxCount
    );









__declspec(deprecated("This function or variable may be unsafe. Consider using " "mbstowcs_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) __declspec(dllimport) size_t __cdecl mbstowcs( wchar_t *_Dest, char const* _Source, size_t _MaxCount);







__declspec(dllimport) errno_t __cdecl _mbstowcs_s_l(
                                                     size_t*     _PtNumOfCharConverted,
     wchar_t*    _DstBuf,
                                                          size_t      _SizeInWords,
                                    char const* _SrcBuf,
                                                          size_t      _MaxCount,
                                                      _locale_t   _Locale
    );










__declspec(deprecated("This function or variable may be unsafe. Consider using " "_mbstowcs_s_l" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) __declspec(dllimport) size_t __cdecl _mbstowcs_l( wchar_t *_Dest, char const* _Source, size_t _MaxCount, _locale_t _Locale);











__declspec(deprecated("This function or variable may be unsafe. Consider using " "wctomb_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
__declspec(dllimport) int __cdecl wctomb(
     char*   _MbCh,
                               wchar_t _WCh
    );

__declspec(deprecated("This function or variable may be unsafe. Consider using " "_wctomb_s_l" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
__declspec(dllimport) int __cdecl _wctomb_l(
      char*     _MbCh,
                         wchar_t   _WCh,
                     _locale_t _Locale
    );



    
    __declspec(dllimport) errno_t __cdecl wctomb_s(
                                                        int*    _SizeConverted,
         char*   _MbCh,
                                                             rsize_t _SizeInBytes,
                                                             wchar_t _WCh
        );

#line 986 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"


__declspec(dllimport) errno_t __cdecl _wctomb_s_l(
                            int*     _SizeConverted,
     char*     _MbCh,
                                 size_t    _SizeInBytes,
                                 wchar_t   _WCh,
                             _locale_t _Locale);


__declspec(dllimport) errno_t __cdecl wcstombs_s(
                                                              size_t*        _PtNumOfCharConverted,
     char*          _Dst,
                                                                   size_t         _DstSizeInBytes,
                                                                 wchar_t const* _Src,
                                                                   size_t         _MaxCountInBytes
    );









__declspec(deprecated("This function or variable may be unsafe. Consider using " "wcstombs_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) __declspec(dllimport) size_t __cdecl wcstombs( char *_Dest, wchar_t const* _Source, size_t _MaxCount);







__declspec(dllimport) errno_t __cdecl _wcstombs_s_l(
                                                              size_t*        _PtNumOfCharConverted,
     char*          _Dst,
                                                                   size_t         _DstSizeInBytes,
                                                                 wchar_t const* _Src,
                                                                   size_t         _MaxCountInBytes,
                                                               _locale_t      _Locale
    );










__declspec(deprecated("This function or variable may be unsafe. Consider using " "_wcstombs_s_l" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) __declspec(dllimport) size_t __cdecl _wcstombs_l( char *_Dest, wchar_t const* _Source, size_t _MaxCount, _locale_t _Locale);





























__declspec(dllimport) __declspec(allocator) char* __cdecl _fullpath(
     char*       _Buffer,
                               char const* _Path,
                                 size_t      _BufferCount
    );




__declspec(dllimport) errno_t __cdecl _makepath_s(
     char*       _Buffer,
                             size_t      _BufferCount,
                       char const* _Drive,
                       char const* _Dir,
                       char const* _Filename,
                       char const* _Ext
    );










__declspec(deprecated("This function or variable may be unsafe. Consider using " "_makepath_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) __declspec(dllimport) void __cdecl _makepath( char *_Buffer, char const* _Drive, char const* _Dir, char const* _Filename, char const* _Ext);








__declspec(deprecated("This function or variable may be unsafe. Consider using " "_splitpath_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
__declspec(dllimport) void __cdecl _splitpath(
                       char const* _FullPath,
      char*       _Drive,
      char*       _Dir,
      char*       _Filename,
      char*       _Ext
    );


__declspec(dllimport) errno_t __cdecl _splitpath_s(
                                 char const* _FullPath,
        char*       _Drive,
                                   size_t      _DriveCount,
          char*       _Dir,
                                   size_t      _DirCount,
     char*       _Filename,
                                   size_t      _FilenameCount,
          char*       _Ext,
                                   size_t      _ExtCount
    );







__declspec(dllimport) errno_t __cdecl getenv_s(
                                size_t*     _RequiredCount,
     char*       _Buffer,
                                 rsize_t     _BufferCount,
                               char const* _VarName
    );

#line 1140 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"




__declspec(dllimport) int*       __cdecl __p___argc (void);
__declspec(dllimport) char***    __cdecl __p___argv (void);
__declspec(dllimport) wchar_t*** __cdecl __p___wargv(void);






    
    
    
#line 1157 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"

__declspec(dllimport) char***    __cdecl __p__environ (void);
__declspec(dllimport) wchar_t*** __cdecl __p__wenviron(void);


    
#line 1164 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"







    
    
#line 1174 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"









     __declspec(deprecated("This function or variable may be unsafe. Consider using " "_dupenv_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
    __declspec(dllimport) char* __cdecl getenv(
         char const* _VarName
        );

    






    


#line 1199 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"

    
    __declspec(dllimport) errno_t __cdecl _dupenv_s(
          char**      _Buffer,
                                                                           size_t*     _BufferCount,
                                                                              char const* _VarName
        );

    

#line 1210 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"

    __declspec(dllimport) int __cdecl system(
         char const* _Command
        );

    
    
    #pragma warning(push)
    #pragma warning(disable: 6540)

    
    __declspec(dllimport) int __cdecl _putenv(
         char const* _EnvString
        );

    
    __declspec(dllimport) errno_t __cdecl _putenv_s(
         char const* _Name,
         char const* _Value
        );

    #pragma warning(pop)

    __declspec(dllimport) errno_t __cdecl _searchenv_s(
                               char const* _Filename,
                               char const* _VarName,
         char*       _Buffer,
                                 size_t      _BufferCount
        );

    






    __declspec(deprecated("This function or variable may be unsafe. Consider using " "_searchenv_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) __declspec(dllimport) void __cdecl _searchenv(char const* _Filename, char const* _VarName, char *_Buffer);






    
    __declspec(deprecated("This function or variable has been superceded by newer library " "or operating system functionality. Consider using " "SetErrorMode" " " "instead. See online help for details."))
    __declspec(dllimport) void __cdecl _seterrormode(
         int _Mode
        );

    __declspec(deprecated("This function or variable has been superceded by newer library " "or operating system functionality. Consider using " "Beep" " " "instead. See online help for details."))
    __declspec(dllimport) void __cdecl _beep(
         unsigned _Frequency,
         unsigned _Duration
        );

    __declspec(deprecated("This function or variable has been superceded by newer library " "or operating system functionality. Consider using " "Sleep" " " "instead. See online help for details."))
    __declspec(dllimport) void __cdecl _sleep(
         unsigned long _Duration
        );

#line 1272 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"









    
        
        
    #line 1285 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"

    
    

    #pragma warning(push)
    #pragma warning(disable: 4141) 

     __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_ecvt" ". See online help for details.")) __declspec(deprecated("This function or variable may be unsafe. Consider using " "_ecvt_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
    __declspec(dllimport) char* __cdecl ecvt(
          double _Value,
          int    _DigitCount,
         int*   _PtDec,
         int*   _PtSign
        );

     __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_fcvt" ". See online help for details.")) __declspec(deprecated("This function or variable may be unsafe. Consider using " "_fcvt_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
    __declspec(dllimport) char* __cdecl fcvt(
          double _Value,
          int    _FractionalDigitCount,
         int*   _PtDec,
         int*   _PtSign
        );

    __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_gcvt" ". See online help for details.")) __declspec(deprecated("This function or variable may be unsafe. Consider using " "_fcvt_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
    __declspec(dllimport) char* __cdecl gcvt(
                           double _Value,
                           int    _DigitCount,
          char*  _DstBuf
        );

    __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_itoa" ". See online help for details.")) __declspec(deprecated("This function or variable may be unsafe. Consider using " "_itoa_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
    __declspec(dllimport) char* __cdecl itoa(
                           int   _Value,
          char* _Buffer,
                           int   _Radix
        );

    __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_ltoa" ". See online help for details.")) __declspec(deprecated("This function or variable may be unsafe. Consider using " "_ltoa_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
    __declspec(dllimport) char* __cdecl ltoa(
                           long  _Value,
          char* _Buffer,
                           int   _Radix
        );


    __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_swab" ". See online help for details."))
    __declspec(dllimport) void __cdecl swab(
         char* _Buf1,
         char* _Buf2,
                                    int   _SizeInBytes
        );

    __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_ultoa" ". See online help for details.")) __declspec(deprecated("This function or variable may be unsafe. Consider using " "_ultoa_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
    __declspec(dllimport) char* __cdecl ultoa(
                           unsigned long _Value,
          char*         _Buffer,
                           int           _Radix
        );

    

     __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_putenv" ". See online help for details."))
    __declspec(dllimport) int __cdecl putenv(
         char const* _EnvString
        );

    #pragma warning(pop)

    _onexit_t __cdecl onexit( _onexit_t _Func);

#line 1356 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"



__pragma(pack(pop))

#pragma warning(pop) 
#line 1363 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdlib.h"
#pragma external_header(pop)
#line 11 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.c"





#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_xmacro_def.h"
























#line 17 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.c"









struct mk_hash_function_crc32_s { enum mk_hash_function_crc32 m_tag; struct mk_hash_hash_crc32_s m_val; }; struct mk_hash_function_md2_s { enum mk_hash_function_md2 m_tag; struct mk_hash_hash_md2_s m_val; }; struct mk_hash_function_md4_s { enum mk_hash_function_md4 m_tag; struct mk_hash_hash_md4_s m_val; }; struct mk_hash_function_md5_s { enum mk_hash_function_md5 m_tag; struct mk_hash_hash_md5_s m_val; }; struct mk_hash_function_sha1_s { enum mk_hash_function_sha1 m_tag; struct mk_hash_hash_sha1_s m_val; }; struct mk_hash_function_sha2_224_s { enum mk_hash_function_sha2_224 m_tag; struct mk_hash_hash_sha2_224_s m_val; }; struct mk_hash_function_sha2_256_s { enum mk_hash_function_sha2_256 m_tag; struct mk_hash_hash_sha2_256_s m_val; }; struct mk_hash_function_sha2_384_s { enum mk_hash_function_sha2_384 m_tag; struct mk_hash_hash_sha2_384_s m_val; }; struct mk_hash_function_sha2_512_s { enum mk_hash_function_sha2_512 m_tag; struct mk_hash_hash_sha2_512_s m_val; }; struct mk_hash_function_sha2_512224_s { enum mk_hash_function_sha2_512224 m_tag; struct mk_hash_hash_sha2_512224_s m_val; }; struct mk_hash_function_sha2_512256_s { enum mk_hash_function_sha2_512256 m_tag; struct mk_hash_hash_sha2_512256_s m_val; }; struct mk_hash_function_sha3_224_s { enum mk_hash_function_sha3_224 m_tag; struct mk_hash_hash_sha3_224_s m_val; }; struct mk_hash_function_sha3_256_s { enum mk_hash_function_sha3_256 m_tag; struct mk_hash_hash_sha3_256_s m_val; }; struct mk_hash_function_sha3_384_s { enum mk_hash_function_sha3_384 m_tag; struct mk_hash_hash_sha3_384_s m_val; }; struct mk_hash_function_sha3_512_s { enum mk_hash_function_sha3_512 m_tag; struct mk_hash_hash_sha3_512_s m_val; };




#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_xmacro_undef.h"









#line 32 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.c"


 mk_hash_function_h mk_hash_function_create(enum mk_hash_e type)
{
	mk_hash_function_h hash_function;

	__assume(( ((type) == mk_hash_e_crc32) || ((type) == mk_hash_e_md2) || ((type) == mk_hash_e_md4) || ((type) == mk_hash_e_md5) || ((type) == mk_hash_e_sha1) || ((type) == mk_hash_e_sha2_224) || ((type) == mk_hash_e_sha2_256) || ((type) == mk_hash_e_sha2_384) || ((type) == mk_hash_e_sha2_512) || ((type) == mk_hash_e_sha2_512224) || ((type) == mk_hash_e_sha2_512256) || ((type) == mk_hash_e_sha3_224) || ((type) == mk_hash_e_sha3_256) || ((type) == mk_hash_e_sha3_384) || ((type) == mk_hash_e_sha3_512) )) ;

	mk_clobber(&hash_function);
	switch(type)
	{
		#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_xmacro_def.h"
























#line 44 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.c"
		
		
		
		








		case mk_hash_e_crc32: { struct mk_hash_function_crc32_s* obj = (struct mk_hash_function_crc32_s*)malloc(sizeof(struct mk_hash_function_crc32_s)); if(obj) mk_hash_hash_crc32_init(&obj->m_val); hash_function.m_val = obj; return hash_function; } break; case mk_hash_e_md2: { struct mk_hash_function_md2_s* obj = (struct mk_hash_function_md2_s*)malloc(sizeof(struct mk_hash_function_md2_s)); if(obj) mk_hash_hash_md2_init(&obj->m_val); hash_function.m_val = obj; return hash_function; } break; case mk_hash_e_md4: { struct mk_hash_function_md4_s* obj = (struct mk_hash_function_md4_s*)malloc(sizeof(struct mk_hash_function_md4_s)); if(obj) mk_hash_hash_md4_init(&obj->m_val); hash_function.m_val = obj; return hash_function; } break; case mk_hash_e_md5: { struct mk_hash_function_md5_s* obj = (struct mk_hash_function_md5_s*)malloc(sizeof(struct mk_hash_function_md5_s)); if(obj) mk_hash_hash_md5_init(&obj->m_val); hash_function.m_val = obj; return hash_function; } break; case mk_hash_e_sha1: { struct mk_hash_function_sha1_s* obj = (struct mk_hash_function_sha1_s*)malloc(sizeof(struct mk_hash_function_sha1_s)); if(obj) mk_hash_hash_sha1_init(&obj->m_val); hash_function.m_val = obj; return hash_function; } break; case mk_hash_e_sha2_224: { struct mk_hash_function_sha2_224_s* obj = (struct mk_hash_function_sha2_224_s*)malloc(sizeof(struct mk_hash_function_sha2_224_s)); if(obj) mk_hash_hash_sha2_224_init(&obj->m_val); hash_function.m_val = obj; return hash_function; } break; case mk_hash_e_sha2_256: { struct mk_hash_function_sha2_256_s* obj = (struct mk_hash_function_sha2_256_s*)malloc(sizeof(struct mk_hash_function_sha2_256_s)); if(obj) mk_hash_hash_sha2_256_init(&obj->m_val); hash_function.m_val = obj; return hash_function; } break; case mk_hash_e_sha2_384: { struct mk_hash_function_sha2_384_s* obj = (struct mk_hash_function_sha2_384_s*)malloc(sizeof(struct mk_hash_function_sha2_384_s)); if(obj) mk_hash_hash_sha2_384_init(&obj->m_val); hash_function.m_val = obj; return hash_function; } break; case mk_hash_e_sha2_512: { struct mk_hash_function_sha2_512_s* obj = (struct mk_hash_function_sha2_512_s*)malloc(sizeof(struct mk_hash_function_sha2_512_s)); if(obj) mk_hash_hash_sha2_512_init(&obj->m_val); hash_function.m_val = obj; return hash_function; } break; case mk_hash_e_sha2_512224: { struct mk_hash_function_sha2_512224_s* obj = (struct mk_hash_function_sha2_512224_s*)malloc(sizeof(struct mk_hash_function_sha2_512224_s)); if(obj) mk_hash_hash_sha2_512224_init(&obj->m_val); hash_function.m_val = obj; return hash_function; } break; case mk_hash_e_sha2_512256: { struct mk_hash_function_sha2_512256_s* obj = (struct mk_hash_function_sha2_512256_s*)malloc(sizeof(struct mk_hash_function_sha2_512256_s)); if(obj) mk_hash_hash_sha2_512256_init(&obj->m_val); hash_function.m_val = obj; return hash_function; } break; case mk_hash_e_sha3_224: { struct mk_hash_function_sha3_224_s* obj = (struct mk_hash_function_sha3_224_s*)malloc(sizeof(struct mk_hash_function_sha3_224_s)); if(obj) mk_hash_hash_sha3_224_init(&obj->m_val); hash_function.m_val = obj; return hash_function; } break; case mk_hash_e_sha3_256: { struct mk_hash_function_sha3_256_s* obj = (struct mk_hash_function_sha3_256_s*)malloc(sizeof(struct mk_hash_function_sha3_256_s)); if(obj) mk_hash_hash_sha3_256_init(&obj->m_val); hash_function.m_val = obj; return hash_function; } break; case mk_hash_e_sha3_384: { struct mk_hash_function_sha3_384_s* obj = (struct mk_hash_function_sha3_384_s*)malloc(sizeof(struct mk_hash_function_sha3_384_s)); if(obj) mk_hash_hash_sha3_384_init(&obj->m_val); hash_function.m_val = obj; return hash_function; } break; case mk_hash_e_sha3_512: { struct mk_hash_function_sha3_512_s* obj = (struct mk_hash_function_sha3_512_s*)malloc(sizeof(struct mk_hash_function_sha3_512_s)); if(obj) mk_hash_hash_sha3_512_init(&obj->m_val); hash_function.m_val = obj; return hash_function; } break;
		
		
		
		
		#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_xmacro_undef.h"









#line 62 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.c"
	}
	return hash_function;
}

 int mk_hash_function_is_good(mk_hash_function_h hash_function)
{
	return ((!!((hash_function).m_val)) && ( ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_crc32) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md2) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md4) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md5) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha1) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_384) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_384) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_512) )) ;
}

 enum mk_hash_e mk_hash_function_get_type(mk_hash_function_h hash_function)
{
	__assume(((!!((hash_function).m_val)) && ( ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_crc32) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md2) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md4) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md5) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha1) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_384) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_384) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_512) ))) ;

	return *(enum mk_hash_e*)(hash_function.m_val);
}

 void mk_hash_function_reinit(mk_hash_function_h hash_function)
{
	enum mk_hash_e type;

	__assume(((!!((hash_function).m_val)) && ( ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_crc32) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md2) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md4) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md5) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha1) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_384) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_384) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_512) ))) ;

	type = mk_hash_function_get_type(hash_function);
	__assume(( ((type) == mk_hash_e_crc32) || ((type) == mk_hash_e_md2) || ((type) == mk_hash_e_md4) || ((type) == mk_hash_e_md5) || ((type) == mk_hash_e_sha1) || ((type) == mk_hash_e_sha2_224) || ((type) == mk_hash_e_sha2_256) || ((type) == mk_hash_e_sha2_384) || ((type) == mk_hash_e_sha2_512) || ((type) == mk_hash_e_sha2_512224) || ((type) == mk_hash_e_sha2_512256) || ((type) == mk_hash_e_sha3_224) || ((type) == mk_hash_e_sha3_256) || ((type) == mk_hash_e_sha3_384) || ((type) == mk_hash_e_sha3_512) )) ;
	switch(type)
	{
		#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_xmacro_def.h"
























#line 89 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.c"
		
		
		
		
		












		case mk_hash_e_crc32: { void* mem; struct mk_hash_function_crc32_s* hash_fun; struct mk_hash_hash_crc32_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_crc32_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_crc32_init(hash); } break; case mk_hash_e_md2: { void* mem; struct mk_hash_function_md2_s* hash_fun; struct mk_hash_hash_md2_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_md2_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_md2_init(hash); } break; case mk_hash_e_md4: { void* mem; struct mk_hash_function_md4_s* hash_fun; struct mk_hash_hash_md4_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_md4_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_md4_init(hash); } break; case mk_hash_e_md5: { void* mem; struct mk_hash_function_md5_s* hash_fun; struct mk_hash_hash_md5_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_md5_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_md5_init(hash); } break; case mk_hash_e_sha1: { void* mem; struct mk_hash_function_sha1_s* hash_fun; struct mk_hash_hash_sha1_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha1_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha1_init(hash); } break; case mk_hash_e_sha2_224: { void* mem; struct mk_hash_function_sha2_224_s* hash_fun; struct mk_hash_hash_sha2_224_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_224_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_224_init(hash); } break; case mk_hash_e_sha2_256: { void* mem; struct mk_hash_function_sha2_256_s* hash_fun; struct mk_hash_hash_sha2_256_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_256_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_256_init(hash); } break; case mk_hash_e_sha2_384: { void* mem; struct mk_hash_function_sha2_384_s* hash_fun; struct mk_hash_hash_sha2_384_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_384_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_384_init(hash); } break; case mk_hash_e_sha2_512: { void* mem; struct mk_hash_function_sha2_512_s* hash_fun; struct mk_hash_hash_sha2_512_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_512_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_512_init(hash); } break; case mk_hash_e_sha2_512224: { void* mem; struct mk_hash_function_sha2_512224_s* hash_fun; struct mk_hash_hash_sha2_512224_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_512224_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_512224_init(hash); } break; case mk_hash_e_sha2_512256: { void* mem; struct mk_hash_function_sha2_512256_s* hash_fun; struct mk_hash_hash_sha2_512256_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_512256_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_512256_init(hash); } break; case mk_hash_e_sha3_224: { void* mem; struct mk_hash_function_sha3_224_s* hash_fun; struct mk_hash_hash_sha3_224_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha3_224_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha3_224_init(hash); } break; case mk_hash_e_sha3_256: { void* mem; struct mk_hash_function_sha3_256_s* hash_fun; struct mk_hash_hash_sha3_256_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha3_256_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha3_256_init(hash); } break; case mk_hash_e_sha3_384: { void* mem; struct mk_hash_function_sha3_384_s* hash_fun; struct mk_hash_hash_sha3_384_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha3_384_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha3_384_init(hash); } break; case mk_hash_e_sha3_512: { void* mem; struct mk_hash_function_sha3_512_s* hash_fun; struct mk_hash_hash_sha3_512_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha3_512_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha3_512_init(hash); } break;
		
		
		
		
		
		#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_xmacro_undef.h"









#line 113 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.c"
	}
}

 void mk_hash_function_append(mk_hash_function_h hash_function, void const* msg, int msg_len)
{
	enum mk_hash_e type;

	__assume(((!!((hash_function).m_val)) && ( ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_crc32) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md2) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md4) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md5) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha1) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_384) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_384) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_512) ))) ;
	__assume(msg || msg_len == 0) ;
	__assume(msg_len >= 0) ;

	type = mk_hash_function_get_type(hash_function);
	__assume(( ((type) == mk_hash_e_crc32) || ((type) == mk_hash_e_md2) || ((type) == mk_hash_e_md4) || ((type) == mk_hash_e_md5) || ((type) == mk_hash_e_sha1) || ((type) == mk_hash_e_sha2_224) || ((type) == mk_hash_e_sha2_256) || ((type) == mk_hash_e_sha2_384) || ((type) == mk_hash_e_sha2_512) || ((type) == mk_hash_e_sha2_512224) || ((type) == mk_hash_e_sha2_512256) || ((type) == mk_hash_e_sha3_224) || ((type) == mk_hash_e_sha3_256) || ((type) == mk_hash_e_sha3_384) || ((type) == mk_hash_e_sha3_512) )) ;
	switch(type)
	{
		#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_xmacro_def.h"
























#line 129 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.c"
		
		
		
		
		












		case mk_hash_e_crc32: { void* mem; struct mk_hash_function_crc32_s* hash_fun; struct mk_hash_hash_crc32_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_crc32_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_crc32_append(hash, msg, msg_len); } break; case mk_hash_e_md2: { void* mem; struct mk_hash_function_md2_s* hash_fun; struct mk_hash_hash_md2_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_md2_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_md2_append(hash, msg, msg_len); } break; case mk_hash_e_md4: { void* mem; struct mk_hash_function_md4_s* hash_fun; struct mk_hash_hash_md4_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_md4_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_md4_append(hash, msg, msg_len); } break; case mk_hash_e_md5: { void* mem; struct mk_hash_function_md5_s* hash_fun; struct mk_hash_hash_md5_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_md5_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_md5_append(hash, msg, msg_len); } break; case mk_hash_e_sha1: { void* mem; struct mk_hash_function_sha1_s* hash_fun; struct mk_hash_hash_sha1_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha1_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha1_append(hash, msg, msg_len); } break; case mk_hash_e_sha2_224: { void* mem; struct mk_hash_function_sha2_224_s* hash_fun; struct mk_hash_hash_sha2_224_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_224_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_224_append(hash, msg, msg_len); } break; case mk_hash_e_sha2_256: { void* mem; struct mk_hash_function_sha2_256_s* hash_fun; struct mk_hash_hash_sha2_256_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_256_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_256_append(hash, msg, msg_len); } break; case mk_hash_e_sha2_384: { void* mem; struct mk_hash_function_sha2_384_s* hash_fun; struct mk_hash_hash_sha2_384_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_384_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_384_append(hash, msg, msg_len); } break; case mk_hash_e_sha2_512: { void* mem; struct mk_hash_function_sha2_512_s* hash_fun; struct mk_hash_hash_sha2_512_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_512_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_512_append(hash, msg, msg_len); } break; case mk_hash_e_sha2_512224: { void* mem; struct mk_hash_function_sha2_512224_s* hash_fun; struct mk_hash_hash_sha2_512224_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_512224_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_512224_append(hash, msg, msg_len); } break; case mk_hash_e_sha2_512256: { void* mem; struct mk_hash_function_sha2_512256_s* hash_fun; struct mk_hash_hash_sha2_512256_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_512256_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_512256_append(hash, msg, msg_len); } break; case mk_hash_e_sha3_224: { void* mem; struct mk_hash_function_sha3_224_s* hash_fun; struct mk_hash_hash_sha3_224_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha3_224_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha3_224_append(hash, msg, msg_len); } break; case mk_hash_e_sha3_256: { void* mem; struct mk_hash_function_sha3_256_s* hash_fun; struct mk_hash_hash_sha3_256_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha3_256_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha3_256_append(hash, msg, msg_len); } break; case mk_hash_e_sha3_384: { void* mem; struct mk_hash_function_sha3_384_s* hash_fun; struct mk_hash_hash_sha3_384_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha3_384_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha3_384_append(hash, msg, msg_len); } break; case mk_hash_e_sha3_512: { void* mem; struct mk_hash_function_sha3_512_s* hash_fun; struct mk_hash_hash_sha3_512_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha3_512_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha3_512_append(hash, msg, msg_len); } break;
		
		
		
		
		
		#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_xmacro_undef.h"









#line 153 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.c"
	}
}

 void mk_hash_function_finish(mk_hash_function_h hash_function, void* digest)
{
	enum mk_hash_e type;
	
	__assume(((!!((hash_function).m_val)) && ( ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_crc32) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md2) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md4) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md5) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha1) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_384) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_384) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_512) ))) ;
	__assume(digest) ;

	type = mk_hash_function_get_type(hash_function);
	__assume(( ((type) == mk_hash_e_crc32) || ((type) == mk_hash_e_md2) || ((type) == mk_hash_e_md4) || ((type) == mk_hash_e_md5) || ((type) == mk_hash_e_sha1) || ((type) == mk_hash_e_sha2_224) || ((type) == mk_hash_e_sha2_256) || ((type) == mk_hash_e_sha2_384) || ((type) == mk_hash_e_sha2_512) || ((type) == mk_hash_e_sha2_512224) || ((type) == mk_hash_e_sha2_512256) || ((type) == mk_hash_e_sha3_224) || ((type) == mk_hash_e_sha3_256) || ((type) == mk_hash_e_sha3_384) || ((type) == mk_hash_e_sha3_512) )) ;
	switch(type)
	{
		#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_xmacro_def.h"
























#line 168 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.c"
		
		
		
		
		












		case mk_hash_e_crc32: { void* mem; struct mk_hash_function_crc32_s* hash_fun; struct mk_hash_hash_crc32_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_crc32_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_crc32_finish(hash, digest); } break; case mk_hash_e_md2: { void* mem; struct mk_hash_function_md2_s* hash_fun; struct mk_hash_hash_md2_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_md2_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_md2_finish(hash, digest); } break; case mk_hash_e_md4: { void* mem; struct mk_hash_function_md4_s* hash_fun; struct mk_hash_hash_md4_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_md4_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_md4_finish(hash, digest); } break; case mk_hash_e_md5: { void* mem; struct mk_hash_function_md5_s* hash_fun; struct mk_hash_hash_md5_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_md5_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_md5_finish(hash, digest); } break; case mk_hash_e_sha1: { void* mem; struct mk_hash_function_sha1_s* hash_fun; struct mk_hash_hash_sha1_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha1_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha1_finish(hash, digest); } break; case mk_hash_e_sha2_224: { void* mem; struct mk_hash_function_sha2_224_s* hash_fun; struct mk_hash_hash_sha2_224_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_224_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_224_finish(hash, digest); } break; case mk_hash_e_sha2_256: { void* mem; struct mk_hash_function_sha2_256_s* hash_fun; struct mk_hash_hash_sha2_256_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_256_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_256_finish(hash, digest); } break; case mk_hash_e_sha2_384: { void* mem; struct mk_hash_function_sha2_384_s* hash_fun; struct mk_hash_hash_sha2_384_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_384_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_384_finish(hash, digest); } break; case mk_hash_e_sha2_512: { void* mem; struct mk_hash_function_sha2_512_s* hash_fun; struct mk_hash_hash_sha2_512_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_512_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_512_finish(hash, digest); } break; case mk_hash_e_sha2_512224: { void* mem; struct mk_hash_function_sha2_512224_s* hash_fun; struct mk_hash_hash_sha2_512224_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_512224_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_512224_finish(hash, digest); } break; case mk_hash_e_sha2_512256: { void* mem; struct mk_hash_function_sha2_512256_s* hash_fun; struct mk_hash_hash_sha2_512256_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha2_512256_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha2_512256_finish(hash, digest); } break; case mk_hash_e_sha3_224: { void* mem; struct mk_hash_function_sha3_224_s* hash_fun; struct mk_hash_hash_sha3_224_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha3_224_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha3_224_finish(hash, digest); } break; case mk_hash_e_sha3_256: { void* mem; struct mk_hash_function_sha3_256_s* hash_fun; struct mk_hash_hash_sha3_256_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha3_256_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha3_256_finish(hash, digest); } break; case mk_hash_e_sha3_384: { void* mem; struct mk_hash_function_sha3_384_s* hash_fun; struct mk_hash_hash_sha3_384_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha3_384_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha3_384_finish(hash, digest); } break; case mk_hash_e_sha3_512: { void* mem; struct mk_hash_function_sha3_512_s* hash_fun; struct mk_hash_hash_sha3_512_s* hash; ((void)0); mem = hash_function.m_val; hash_fun = (struct mk_hash_function_sha3_512_s*)mem; hash = &hash_fun->m_val; mk_hash_hash_sha3_512_finish(hash, digest); } break;
		
		
		
		
		
		#line 1 "C:\\dev\\repos\\mk_crypto\\src\\hash\\base\\mk_hash_base_xmacro_undef.h"









#line 192 "C:\\dev\\repos\\mk_crypto\\src\\mk_hash_function.c"
	}
}

 void mk_hash_function_destroy(mk_hash_function_h hash_function)
{
	__assume(((!!((hash_function).m_val)) && ( ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_crc32) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md2) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md4) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_md5) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha1) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_384) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha2_512256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_224) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_256) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_384) || ((*((enum mk_hash_e*)((hash_function).m_val))) == mk_hash_e_sha3_512) )) || !hash_function.m_val) ;

	free(hash_function.m_val);
}



