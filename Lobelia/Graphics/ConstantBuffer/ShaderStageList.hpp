#pragma once
namespace Lobelia::Graphics {
	//TODO: ���̌ォ�炷�ׂăR���X�^���g�o�b�t�@�͂����ɕς��Ă����\��
	enum ShaderStageList :byte {
		VS = 1,
		PS = 2,
		HS = 4,
		GS = 8,
		DS = 16,
		CS = 32,
	};
}