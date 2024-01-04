/* Copyright (c) 2019-2024 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __X86_SYSCALL_TEST_EBP

/*[[[deemon
print "#define __X86_SYSCALL_TEST_EBP \\";
for (local x: [-128:128+1]) {
	print "	\".ifc %1,"+(x*4)+"(%%ebp);.Lbp%==1;.endif\\n\" \\";
}
print "/" "**" "/";
]]]*/
#define __X86_SYSCALL_TEST_EBP \
	".ifc %1,-512(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-508(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-504(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-500(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-496(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-492(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-488(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-484(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-480(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-476(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-472(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-468(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-464(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-460(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-456(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-452(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-448(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-444(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-440(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-436(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-432(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-428(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-424(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-420(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-416(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-412(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-408(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-404(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-400(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-396(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-392(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-388(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-384(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-380(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-376(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-372(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-368(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-364(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-360(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-356(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-352(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-348(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-344(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-340(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-336(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-332(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-328(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-324(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-320(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-316(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-312(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-308(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-304(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-300(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-296(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-292(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-288(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-284(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-280(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-276(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-272(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-268(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-264(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-260(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-256(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-252(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-248(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-244(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-240(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-236(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-232(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-228(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-224(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-220(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-216(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-212(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-208(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-204(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-200(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-196(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-192(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-188(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-184(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-180(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-176(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-172(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-168(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-164(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-160(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-156(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-152(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-148(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-144(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-140(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-136(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-132(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-128(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-124(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-120(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-116(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-112(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-108(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-104(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-100(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-96(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-92(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-88(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-84(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-80(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-76(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-72(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-68(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-64(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-60(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-56(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-52(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-48(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-44(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-40(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-36(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-32(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-28(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-24(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-20(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-16(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-12(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-8(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,-4(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,0(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,4(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,8(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,12(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,16(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,20(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,24(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,28(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,32(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,36(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,40(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,44(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,48(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,52(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,56(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,60(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,64(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,68(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,72(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,76(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,80(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,84(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,88(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,92(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,96(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,100(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,104(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,108(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,112(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,116(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,120(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,124(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,128(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,132(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,136(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,140(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,144(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,148(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,152(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,156(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,160(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,164(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,168(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,172(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,176(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,180(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,184(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,188(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,192(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,196(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,200(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,204(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,208(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,212(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,216(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,220(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,224(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,228(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,232(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,236(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,240(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,244(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,248(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,252(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,256(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,260(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,264(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,268(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,272(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,276(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,280(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,284(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,288(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,292(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,296(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,300(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,304(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,308(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,312(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,316(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,320(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,324(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,328(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,332(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,336(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,340(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,344(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,348(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,352(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,356(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,360(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,364(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,368(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,372(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,376(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,380(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,384(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,388(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,392(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,396(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,400(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,404(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,408(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,412(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,416(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,420(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,424(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,428(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,432(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,436(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,440(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,444(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,448(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,452(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,456(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,460(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,464(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,468(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,472(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,476(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,480(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,484(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,488(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,492(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,496(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,500(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,504(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,508(%%ebp);.Lbp%==1;.endif\n" \
	".ifc %1,512(%%ebp);.Lbp%==1;.endif\n" \
/**/
//[[[end]]]

#endif /* !__X86_SYSCALL_TEST_EBP */
