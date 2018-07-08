#pragma once

#include "common.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture2D.h"
#include "VertexLayout.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// ���_�o�b�t�@��C���f�b�N�X�o�b�t�@���܂Ƃ߂�ėp�O���t�B�b�N�X ���\�[�X�ł��B
        /// </summary>
        public ref class GraphicsModel
        {
            using Vector2 = ZephyrSharp::Linalg::Vector2;
            using Vector3 = ZephyrSharp::Linalg::Vector3;
            using Vector4 = ZephyrSharp::Linalg::Vector4;
            using Flags = System::FlagsAttribute;

        public:

            virtual ~GraphicsModel()
            {
                this->!GraphicsModel();
            }

            !GraphicsModel()
            {
                delete this->VertexPositions;
                this->VertexPositions = nullptr;

                delete this->VertexNormals;
                this->VertexNormals = nullptr;

                delete this->VertexTextureCoords;
                this->VertexTextureCoords = nullptr;

                delete this->VertexColors;
                this->VertexColors = nullptr;

                delete this->VertexTangents;
                this->VertexTangents = nullptr;

                delete this->VertexIndices;
                this->VertexIndices = nullptr;

                delete this->Texture;
                this->Texture = nullptr;

                delete this->NormalMap;
                this->NormalMap = nullptr;

                delete this->ChildModels;
                this->ChildModels = nullptr;
            }

            /// <summary>
            /// FBX �t�@�C������ 3D ���f�����쐬���܂��B
            /// </summary>
            /// <param name="path">�t�@�C���p�X�B</param> 
            void CreateFromFBX(String^ path);

            /// <summary>
            /// �Ǝ��t�H�[�}�b�g�̃O���t�B�b�N ���f����ǂݍ��݂܂��B
            /// </summary>
            /// <param name="path">�t�@�C���p�X�B</param> 
            void CreateFromCX(String^ path);

            /// <summary>
            /// ���a 1 �̋��̃��f�����쐬���܂��B���f���̒��_�̓C���f�b�N�X�t������Ă���A���[�J�����W�y�і@���x�N�g���������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
            /// </summary>
            /// <param name="slices">�厲����]���Ƃ����X���C�X�̐��B</param>
            /// <param name="stacks">�厲�ɉ������X�^�b�N���B</param>
            void CreateSphere(int slices, int stacks);

            /// <summary>
            /// ��Ђ̒����� 1 �̗����̃��f���𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă���A���[�J�����W�y�і@���x�N�g���������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
            /// </summary>
            void CreateBox();

            /// <summary>
            /// ���s 1�A���a 1 �̉~�����f���𐶐����܂��B���������~�����f���́A Z ��������݂ĉ~�Ɍ����郂�f���ɂȂ�܂��B���f���̒��_�̓C���f�b�N�X�t������Ă���A�ʒu�y�і@���x�N�g���������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
            /// </summary>
            /// <param name="slices">�厲����]���Ƃ����X���C�X�̐��B</param>
            void CreateCylinder(int slices, int stacks);

            /// <summary>
            /// �g�[���X���f���𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă���A���[�J�����W�y�і@���x�N�g���������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
            /// </summary>
            void CreateTorus();

            /// <summary>
            /// �e�B�[�|�b�g���f���𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă���A���[�J�����W�y�і@���x�N�g���������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
            /// </summary>
            void CreateTeapot();

            /// <summary>
            /// �������X�g�𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă��炸�A���[�J�����W�݂̂������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
            /// </summary>
            /// <param name="positions">�����̎n�_�̈ʒu�y�яI�_�̈ʒu�̔z��B�z��̗v�f���́A�Q�̔{���łȂ���΂Ȃ�Ȃ��B</param>
            void CreateLineList(array<Vector3>^ positions);

            /// <summary>
            /// �������X�g�𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă��炸�A���[�J�����W�ƒ��_�J���[�������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
            /// </summary>
            /// <param name="positions">�����̎n�_�̈ʒu�y�яI�_�̈ʒu�̔z��B�z��̗v�f���́A�Q�̔{���łȂ���΂Ȃ�Ȃ��B</param>
            /// <param name="colors">�e���_�̐F���`���钸�_�J���[�B</param>
            void CreateLineList(array<Vector3>^ positions, array<Color>^ colors);

            /// <summary>
            /// �A�������̐����𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă��炸�A���[�J�����W�݂̂������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
            /// </summary>
            /// <param name="positions">���_�̈ʒu�̔z��B</param>
            void CreateLineStrip(array<Vector3>^ positions);

            /// <summary>
            /// �A�������̐����𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă��炸�A���[�J�����W�ƒ��_�J���[�������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
            /// </summary>
            /// <param name="positions">�ߓ_�̈ʒu�̔z��B</param>
            /// <param name="colors">�e���_�̐F���`���钸�_�J���[�B</param>
            void CreateLineStrip(array<Vector3>^ positions, array<Color>^ colors);

            /// <summary>
            /// �r���{�[�h���f���𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă��炸�A���[�J�����W�A�@���x�N�g���A�e�N�X�`�����W�A���_�J���[�������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
            /// </summary>
            void CreateBillBoard();

            /// <summary>
            /// ���b�V���}�b�v ���f���𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă���A���[�J�����W�A�@���x�N�g���������܂��B�}�e���A���ƃe�N�X�`���͐ݒ肳��܂���B
            /// </summary>
            /// <param name="heights">�O���b�h��ɋ�؂������b�V���}�b�v�̊e���_�̍����B�s������ Y ���W�A�񐬕��� X ���W�ɑΉ�����B�s�Ɨ�̐��͓������Ȃ���΂Ȃ�Ȃ��B</param>
            void CreateMeshMap(array<float, 2>^ heights);

        private:

            void CreateFromCX(System::IO::Stream^ stream);

        public:

            /// <summary>
            /// ���_���W�B
            /// </summary>
            VertexBuffer<Vector3>^ VertexPositions = nullptr;

            /// <summary>
            /// ���_�̖@���x�N�g���B
            /// </summary>
            VertexBuffer<Vector3>^ VertexNormals = nullptr;

            /// <summary>
            /// ���_�̃e�N�X�`�����W�B
            /// </summary>
            VertexBuffer<Vector2>^ VertexTextureCoords = nullptr;

            /// <summary>
            /// ���_�̐F�B
            /// </summary>
            VertexBuffer<Color>^ VertexColors = nullptr;

            /// <summary>
            /// ���_�� Tangent�B
            /// </summary>
            VertexBuffer<Vector3>^ VertexTangents = nullptr;

            /// <summary>
            /// ���_�� Binormal�B
            /// </summary>
            VertexBuffer<Vector3>^ VertexBinormals = nullptr;

            /// <summary>
            /// ���_�C���f�b�N�X�B
            /// </summary>
            IndexBuffer^ VertexIndices = nullptr;

            /// <summary>
            /// �e�N�X�`���B
            /// </summary>
            Texture2D^ Texture = nullptr;

            /// <summary>
            /// �@���}�b�v�e�N�X�`���B
            /// </summary>
            Texture2D^ NormalMap = nullptr;

            /// <summary>
            /// �}�e���A�����B
            /// </summary>
            Material Material;

            /// <summary>
            /// �v���~�e�B�u�̍\���B
            /// </summary>
            PrimitiveTopology Topology;

            /// <summary>
            /// �q���f���B
            /// </summary>
            array<GraphicsModel^>^ ChildModels = nullptr;
        };
    }
}
