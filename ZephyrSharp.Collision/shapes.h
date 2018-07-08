#pragma once

#include "common.h"

namespace ZephyrSharp
{
    namespace Collision
    {
        /// <summary>
        /// �����̂�\���܂��B
        /// </summary>
        public ref class Box : public INativeWrapper<zephyr::collision::Box>
        {
        public:

            /// <summary>
            /// �ŏ��w���E���W���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            property float MinX
            {
                float get() { return Native->minX; }
                void set(float value) { Native->minX = value; }
            }

            /// <summary>
            /// �ŏ��x���E���W���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            property float MinY
            {
                float get() { return Native->minY; }
                void set(float value) { Native->minY = value; }
            }

            /// <summary>
            /// �ŏ��y���E���W���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            property float MinZ
            {
                float get() { return Native->minZ; }
                void set(float value) { Native->minZ = value; }
            }

            /// <summary>
            /// �ő�w���E���W���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            property float MaxX
            {
                float get() { return Native->maxX; }
                void set(float value) { Native->maxX = value; }
            }

            /// <summary>
            /// �ő�x���E���W���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            property float MaxY
            {
                float get() { return Native->maxY; }
                void set(float value) { Native->maxY = value; }
            }

            /// <summary>
            /// �ő�y���E���W���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            property float MaxZ
            {
                float get() { return Native->maxZ; }
                void set(float value) { Native->maxZ = value; }
            }

            /// <summary>
            /// �����w�肵��X���E���W��ݒ肵�܂��B�������͕����擾���܂��B
            /// </summary>
            property float LengthX
            {
                float get() { return Native->lengthX; }
                void set(float value) { Native->lengthX = value; }
            }

            /// <summary>
            /// �������w�肵��Y���E���W��ݒ肵�܂��B�������͍������擾���܂��B
            /// </summary>
            property float LengthY
            {
                float get() { return Native->lengthY; }
                void set(float value) { Native->lengthY = value; }
            }

            /// <summary>
            /// ���s�����w�肵��Z���E���W��ݒ肵�܂��B�������͉��s�����擾���܂��B
            /// </summary>
            property float LengthZ
            {
                float get() { return Native->lengthZ; }
                void set(float value) { Native->lengthZ = value; }
            }
        };

        /// <summary>
        /// �����̂��\������e�ӂ��AXYZ���ɕ��s�Ȓ����̂�\���܂��B
        /// </summary>
        public ref class AlignedBox : public Box
        {
        };

        /// <summary>
        /// �Ȗʂ�\���܂��B
        /// </summary>
        public ref class CurvedSurface : public INativeWrapper<zephyr::collision::CurvedSurface>
        {
        public:

            /// <summary>
            /// �e���_�̍�����ݒ肵�܂��B
            /// </summary>
            property array<float, 2>^ Heights
            {
                void set(array<float, 2>^ value)
                {
                    Native->heights.resize(value->GetLength(0), value->GetLength(1));
                    pin_ptr<float> ptr = &value[0, 0];
                    Native->heights.copy_from(ptr);
                }
            }
        };

        /// <summary>
        /// �����ɐL�т钼����\���܂��B
        /// </summary>
        public ref class Line : public INativeWrapper<zephyr::collision::Line>
        {
        public:

            /// <summary>
            /// �����x�N�g�����擾�܂��͐ݒ肵�܂��B
            /// </summary>
            property ZephyrSharp::Linalg::Vector3 Direction
            {
                ZephyrSharp::Linalg::Vector3 get()
                {
                    return reinterpret_cast<ZephyrSharp::Linalg::Vector3%>(Native->direction);
                }

                void set(ZephyrSharp::Linalg::Vector3 value)
                {
                    reinterpret_cast<ZephyrSharp::Linalg::Vector3%>(Native->direction) = value;
                }
            }
        };

        /// <summary>
        /// ������\���܂��B
        /// </summary>
        public ref class LineSegment : public INativeWrapper<zephyr::collision::LineSegment>
        {
        public:

            /// <summary>
            /// �����x�N�g�����擾�܂��͐ݒ肵�܂��B
            /// </summary>
            property ZephyrSharp::Linalg::Vector3 Direction
            {
                ZephyrSharp::Linalg::Vector3 get()
                {
                    return reinterpret_cast<ZephyrSharp::Linalg::Vector3%>(Native->direction);
                }
            }
        };

        /// <summary>
        /// �����ɍL���镽�ʂ�\���܂��B
        /// </summary>
        public ref class PlaneSurface : public INativeWrapper<zephyr::collision::PlaneSurface>
        {
        public:

            /// <summary>
            /// �@���x�N�g�����擾�܂��͐ݒ肵�܂��B�@���x�N�g���͐��K������Ă���K�v������܂��B
            /// </summary>
            property ZephyrSharp::Linalg::Vector3 Normal
            {
                ZephyrSharp::Linalg::Vector3 get()
                {
                    return reinterpret_cast<ZephyrSharp::Linalg::Vector3%>(Native->normal);
                }

                void set(ZephyrSharp::Linalg::Vector3 value)
                {
                    reinterpret_cast<ZephyrSharp::Linalg::Vector3%>(Native->normal) = value;
                }
            }
        };

        /// <summary>
        /// �_��\���܂��B
        /// </summary>
        public ref class Point : public INativeWrapper<zephyr::collision::Point>
        {
        };

        /// <summary>
        /// ���̂�\���܂��B
        /// </summary>
        public ref class Sphere : public INativeWrapper<zephyr::collision::Sphere>
        {
        public:

            /// <summary>
            /// ���a���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            property float Radius
            {
                float get() { return Native->radius; }
                void set(float value) { Native->radius = value; }
            }

            /// <summary>
            /// ���a���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            property float Diameter
            {
                float get() { return Native->diameter; }
                void set(float value) { Native->diameter = value; }
            }
        };
    }
}
