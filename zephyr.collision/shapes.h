#pragma once

#include "zephyr\property.h"
#include "zephyr\matrix.h"
#include "zephyr.linalg\linalg.h"

namespace zephyr
{
    namespace collision
    {
        class AbstractShape abstract
        {
        protected:

            using Vector3 = linalg::Vector3;
            using Matrix4x3 = linalg::Matrix4x3;
        };

        /// <summary>
        /// �����̂�\���܂��B
        /// </summary>
        class Box : public AbstractShape
        {
        public:

            /// <summary>
            /// ���_�Ɉʒu���A�e�ӂ̒������P�̗����̂Ƃ��āA�V�����C���X�^���X�����������܂��B
            /// </summary>
            Box()
            {
                this->lengthX = 1;
                this->lengthY = 1;
                this->lengthZ = 1;
            }

            /// <summary>
            /// �ŏ��w���E���W���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            float minX;

            /// <summary>
            /// �ŏ��x���E���W���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            float minY;

            /// <summary>
            /// �ŏ��y���E���W���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            float minZ;

            /// <summary>
            /// �ő�w���E���W���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            float maxX;

            /// <summary>
            /// �ő�x���E���W���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            float maxY;

            /// <summary>
            /// �ő�y���E���W���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            float maxZ;

            /// <summary>
            /// �����w�肵��X���E���W��ݒ肵�܂��B�������͕����擾���܂��B
            /// </summary>
            READWRITE_PROPERTY(float, lengthX, { return this->maxX - this->minX; }, { this->maxX = value / 2; this->minX = -value / 2; });

            /// <summary>
            /// �������w�肵��Y���E���W��ݒ肵�܂��B�������͍������擾���܂��B
            /// </summary>
            READWRITE_PROPERTY(float, lengthY, { return this->maxY - this->minY; }, { this->maxY = value / 2; this->minY = -value / 2; });

            /// <summary>
            /// ���s�����w�肵��Z���E���W��ݒ肵�܂��B�������͉��s�����擾���܂��B
            /// </summary>
            READWRITE_PROPERTY(float, lengthZ, { return this->maxZ - this->minZ; }, { this->maxZ = value / 2; this->minZ = -value / 2; });
        };

        /// <summary>
        /// �����̂��\������e�ӂ��AXYZ���ɕ��s�Ȓ����̂�\���܂��B
        /// </summary>
        class AlignedBox : public Box
        {
        };

        /// <summary>
        /// �����̒��_�ō\������郁�b�V���E�}�b�v��\���܂��B
        /// </summary>
        class CurvedSurface : public AbstractShape
        {
        public:

            /// <summary>
            /// �Ȗʂ��\������e���_�̍������擾�܂��͐ݒ肵�܂��B
            /// </summary>
            matrix<float> heights;
        };

        /// <summary>
        /// �����ɐL�т钼����\���܂��B
        /// </summary>
        class Line : public AbstractShape
        {
        public:

            /// <summary>
            /// �����x�N�g�����擾�܂��͐ݒ肵�܂��B
            /// </summary>
            Vector3 direction;
        };

        /// <summary>
        /// ������\���܂��B
        /// </summary>
        class LineSegment : public AbstractShape
        {
        public:

            /// <summary>
            /// �J�n�ʒu���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            Vector3 begin;

            /// <summary>
            /// �I�[�ʒu���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            Vector3 end;

            /// <summary>
            /// �J�n�ʒu����I�[�ʒu�ւ̑��΃x�N�g�����擾���܂��B
            /// </summary>
            READONLY_PROPERTY(Vector3, direction, const{ return end - begin; });
        };

        /// <summary>
        /// �����ɍL���镽�ʂ�\���܂��B
        /// </summary>
        class PlaneSurface : public AbstractShape
        {
        public:

            /// <summary>
            /// �@���x�N�g�����擾�܂��͐ݒ肵�܂��B�@���x�N�g���͐��K������Ă���K�v������܂��B
            /// </summary>
            Vector3 normal;
        };

        /// <summary>
        /// �_��\���܂��B
        /// </summary>
        class Point : public AbstractShape {};

        /// <summary>
        /// ���̂�\���܂��B
        /// </summary>
        class Sphere : public AbstractShape
        {
        public:

            /// <summary>
            /// ���a���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            float radius = 0.5f;

            /// <summary>
            /// ���a���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            READWRITE_PROPERTY(float, diameter, { return this->radius * 2; }, { this->radius = value / 2; });
        };
    }
}
