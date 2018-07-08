#pragma once

#include "common.h"
#include "enums.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture2D.h"
#include "VertexLayout.h"
#include "zephyr\vector.h"
#include "zephyr\matrix.h"
#include "zephyr.linalg\Vector2.h"
#include "zephyr.linalg\Vector3.h"
#include "zephyr.linalg\Vector4.h"
#include "zephyr.graphics\Material.h"

namespace zephyr
{
    namespace graphics
    {
        namespace d3d11
        {
            class GraphicsModel
            {
                using Vector2 = zephyr::linalg::Vector2;
                using Vector3 = zephyr::linalg::Vector3;
                using Vector4 = zephyr::linalg::Vector4;

            public:

                /// <summary>
                /// FBX �t�@�C������ 3D ���f�����쐬���܂��B
                /// </summary>
                /// <param name="path">�t�@�C���p�X�B</param> 
                void CreateFromFBX(const string& path);

                /// <summary>
                /// �Ǝ��t�H�[�}�b�g�̃O���t�B�b�N ���f����ǂݍ��݂܂��B
                /// </summary>
                /// <param name="path">�t�@�C���p�X�B</param> 
                void CreateFromCX(const string& path);

                /// <summary>
                /// ���a 1 �̋��̃��f�����쐬���܂��B���f���̒��_�̓C���f�b�N�X�t������Ă���A���[�J�����W�y�і@���x�N�g���������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
                /// </summary>
                /// <param name="slices">�厲����]���Ƃ����X���C�X�̐��B</param>
                /// <param name="stacks">�厲�ɉ������X�^�b�N���B</param>
                void CreateSphere(int slices, int stacks);

                /// <summary>
                /// ��Ђ̒����� 1 �̗����̃��f���𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă���A���[�J�����W�y�і@���x�N�g���������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
                /// </summary>
                //void CreateBox();

                /// <summary>
                /// ���s 1�A���a 1 �̉~�����f���𐶐����܂��B���������~�����f���́A Z ��������݂ĉ~�Ɍ����郂�f���ɂȂ�܂��B���f���̒��_�̓C���f�b�N�X�t������Ă���A�ʒu�y�і@���x�N�g���������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
                /// </summary>
                /// <param name="slices">�厲����]���Ƃ����X���C�X�̐��B</param>
                //void CreateCylinder(int slices, int stacks);

                /// <summary>
                /// �g�[���X���f���𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă���A���[�J�����W�y�і@���x�N�g���������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
                /// </summary>
                //void CreateTorus();

                /// <summary>
                /// �e�B�[�|�b�g���f���𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă���A���[�J�����W�y�і@���x�N�g���������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
                /// </summary>
                //void CreateTeapot();

                /// <summary>
                /// �������X�g�𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă��炸�A���[�J�����W�݂̂������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
                /// </summary>
                /// <param name="positions">�����̎n�_�̈ʒu�y�яI�_�̈ʒu�̔z��B�z��̗v�f���́A�Q�̔{���łȂ���΂Ȃ�Ȃ��B</param>
                void CreateLineList(const vector<Vector3>& positions);

                /// <summary>
                /// �������X�g�𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă��炸�A���[�J�����W�ƒ��_�J���[�������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
                /// </summary>
                /// <param name="positions">�����̎n�_�̈ʒu�y�яI�_�̈ʒu�̔z��B�z��̗v�f���́A�Q�̔{���łȂ���΂Ȃ�Ȃ��B</param>
                /// <param name="colors">�e���_�̐F���`���钸�_�J���[�B</param>
                void CreateLineList(const vector<Vector3>& positions, const vector<Color>& colors);

                /// <summary>
                /// �A�������̐����𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă��炸�A���[�J�����W�݂̂������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
                /// </summary>
                /// <param name="positions">���_�̈ʒu�̔z��B</param>
                void CreateLineStrip(const vector<Vector3>& positions);

                /// <summary>
                /// �A�������̐����𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă��炸�A���[�J�����W�ƒ��_�J���[�������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
                /// </summary>
                /// <param name="positions">�ߓ_�̈ʒu�̔z��B</param>
                /// <param name="colors">�e���_�̐F���`���钸�_�J���[�B</param>
                void CreateLineStrip(const vector<Vector3>& positions, const vector<Color>& colors);

                /// <summary>
                /// �r���{�[�h���f���𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă��炸�A���[�J�����W�A�@���x�N�g���A�e�N�X�`�����W�A���_�J���[�������܂��B�}�e���A������уe�N�X�`���͐�������܂���B
                /// </summary>
                void CreateBillBoard();

                /// <summary>
                /// ���b�V���}�b�v ���f���𐶐����܂��B���f���̒��_�̓C���f�b�N�X�t������Ă���A���[�J�����W�A�@���x�N�g���������܂��B�}�e���A���ƃe�N�X�`���͐ݒ肳��܂���B
                /// </summary>
                /// <param name="heights">�O���b�h��ɋ�؂������b�V���}�b�v�̊e���_�̍����B�s������ Y ���W�A�񐬕��� X ���W�ɑΉ�����B�s�Ɨ�̐��͓������Ȃ���΂Ȃ�Ȃ��B</param>
                void CreateMeshMap(const matrix<float>& heights);

            public:

                /// <summary>
                /// ���_���W�B
                /// </summary>
                VertexBuffer VertexPositions;

                /// <summary>
                /// ���_�̖@���x�N�g���B
                /// </summary>
                VertexBuffer VertexNormals;

                /// <summary>
                /// ���_�̃e�N�X�`�����W�B
                /// </summary>
                VertexBuffer VertexTextureCoords;

                /// <summary>
                /// ���_�̐F�B
                /// </summary>
                VertexBuffer VertexColors;

                /// <summary>
                /// ���_�� Tangent�B
                /// </summary>
                VertexBuffer VertexTangents;

                /// <summary>
                /// ���_�� Binormal�B
                /// </summary>
                VertexBuffer VertexBinormals;

                /// <summary>
                /// ���_�C���f�b�N�X�B
                /// </summary>
                IndexBuffer VertexIndices;

                /// <summary>
                /// �e�N�X�`���B
                /// </summary>
                Texture2D Texture;

                /// <summary>
                /// �@���}�b�v�e�N�X�`���B
                /// </summary>
                Texture2D NormalMap;

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
                vector<GraphicsModel> ChildModels;
            };
        }
    }
}
