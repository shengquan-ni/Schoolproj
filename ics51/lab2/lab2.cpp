//
//	ICS 51, Lab #2
//
//	-----------------------------------------------------------------
// 
//	IMPORTATNT NOTES:
//	
//	- To test your code use the tests in lab2-testing.cpp
//	
//	- Write your assembly code only in the marked blocks.
//	
//	- Do NOT change anything outside the marked blocks.
//
//	- Remember to fill in your name, student ID below.
// 
//	- This lab has to be done individually.
//
//  - Use lodepng.h and lodepng.cpp to read/write png files.
//
//  - Two test images are provided to you.
//	
//	- Submit ONLY lab2.cpp file for grading.
// 


char *yourName = "Shengquan Ni";
char *yourStudentID = "46564157";


//
// This function should takes in a square sized grayscale image and applies thresholding on each pixel.
// Width and height of the image are equal to dim.
// NOTE: you can't define additional variables.
//
void imageThresholding(unsigned char* image, int dim) {
	
	__asm {

// YOUR CODE STARTS HERE
	mov eax,image
	mov ecx,dim
	mov bl,80h
	movzx edi,bl
	xor ebx, ebx
		L1:
		push ecx
		mov ecx,dim
			L2:
			mov dl, byte ptr[eax + ebx]
			mov byte ptr[eax + ebx],0x00
			movzx esi,dl
			cmp esi,edi
			jl L3
			mov byte ptr[eax + ebx],0xFF
			L3:
			inc ebx
		loop L2
		pop ecx
	loop L1
// YOUR CODE ENDS HERE

  }
}



// This function flips an square image of given dimension horizontally/vertically.
// Width and height of the image are equal to dim.
// if direction is 0, image should be flipped horizontally
// otherwise image should be flipped vertically.
//
//
// Two variables are definde to help you with implemetanion.
// NOTE: you can't define additional variables.
//
void imageFlip(unsigned int* image, int dim, int direction) {
  
  unsigned int a_p, a_p_m;
  
  __asm {
// YOUR CODE STARTS HERE
    mov eax,image
	mov ecx,dim
	shr ecx,1
	mov esi,direction
	xor edi,edi
		L1:
		push ecx
		mov ecx,dim
		xor ebx, ebx
			L2:
			push ecx
			push ebx
			cmp esi,0h
			jne L3
			add ebx,edi
			xchg ecx, dword ptr[eax + ebx * 4]
			mov edx,dim
			sub edx,edi
			dec edx
			add edx,ebx
			sub edx,edi
			xchg dword ptr[eax + edx * 4], ecx
			xchg dword ptr[eax + ebx * 4], ecx
			pop ebx
			add ebx,dim
			jmp L4
			L3:
			push edi
			imul edi,dim
			add ebx,edi
			pop edi
			xchg ecx, dword ptr[eax + ebx * 4]
			mov edx,dim
			dec edx
			push edi
			add edi,edi
			sub edx,edi
			imul edx,dim
			add edx,ebx
			xchg dword ptr[eax + edx * 4], ecx
			xchg dword ptr[eax + ebx * 4], ecx			
			pop edi
			pop ebx
			inc ebx
			L4:
			pop ecx
		loop L2
		inc edi
		pop ecx
	loop L1
// YOUR CODE ENDS HERE
  }
  
}