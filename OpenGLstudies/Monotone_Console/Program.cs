using System;
using System.Collections.Generic;
using System.Linq;

namespace Monotone_Console
{
    class Program
    {
        static void Main(string[] args)
        {
            //----------------------------------------------------- 샘플
            int MNT_NUM = 50;

            List<float> sample_x = new List<float>() {
                0.28941f, 0.439397f, 0.515231f, -0.608676f, -0.719035f, -0.27297f, 0.39598f, -0.348569f, 0.338582f, -0.402379f,
                -0.356486f, -0.913199f, 0.00906308f, 0.76587f, 0.907783f, -0.0789068f, 0.106984f, 0.758958f, 0.315f, -0.170193f,
                -0.238396f, -0.610595f, 0.0526269f, 0.677162f, 0.26f, -0.153209f, -0.149909f, 0.325937f, -0.35105f, -0.620496f,
                -0.00866025f, -0.391086f, -0.608589f, 0.0146541f, 0.13906f, 0.0138919f, 0.423205f, -0.761151f, -0.319454f, -0.692108f,
                0.0644526f, -0.845723f, -0.529769f, -0.0398478f, 0.180611f, -0.385725f, -0.812215f, -0.0171034f, 0.679586f, 0.592006f
            };

            List<float> sample_y = new List<float>() {
                0.111094f, -0.0230278f, -0.572222f, 0.197771f, 0.350697f, -0.454299f, 0.39598f, 0.536749f, 0.172516f, -0.431499f,
                0.240453f, 0.261855f, -0.00422618f, 0.26371f, 0.063478f, -0.161783f, 0.132115f, 0.0397753f, -0.545596f, -0.0586023f,
                -0.126757f, -0.381542f, -0.172135f, -0.40688f, -0.450333f, 0.128558f, -0.00523492f, 0.0516234f, -0.327359f, 0.520658f,
                -0.005f, -0.246922f, 0.365677f, 0.279616f, 0.231435f, 0.0787846f, -0.582492f, -0.277036f, 0.240726f, 0.198459f,
                0.303226f, 0.307818f, -0.281683f, 0.00348623f, 0.187028f, -0.231767f, 0.31178f, 0.979851f, -0.0237317f, 0.215473f
            };
            //-----------------------------------------------------

            List<int> chain_idx = new List<int>();
            List<XY> monotones = new List<XY>();
            List<XY> debugging = new List<XY>(); // 디버깅용

            XY insert;

            for (int i = 0; i<MNT_NUM; i++)
            {
                chain_idx.Add(i); insert.x = sample_x[i]; insert.y = sample_y[i];
                monotones.Add(insert);
            }

            for (int i = 0; i < 2; i++)
            {
                selection_sort(ref monotones);
                monotones = monotone_test(ref monotones);

                debugging = monotones.Distinct().ToList();
                debugging.Add(debugging[0]);
                for (int j = 0; j < debugging.Count; j++)
                {
                    Console.WriteLine("checked " + j + " : " + debugging[j].x + ", " + debugging[j].y);
                }
                Console.WriteLine("");
            }
        }

        struct XY
        {
            public float x;
            public float y;
        }
        
        /*struct Monotone
        {
            public float x;
            public float y;
            public bool chain;
        }*/

        // 벡터 생성 함수
        static XY vector_gen(ref List<XY> monotones, int start_idx, int end_idx)
        {
            XY vector;

            vector.x = monotones[end_idx].x - monotones[start_idx].x;
            vector.y = monotones[end_idx].y - monotones[start_idx].y;

            return vector;
        }

        // 벡터 Cross 곱
        static float cross_product(ref List<XY> monotones, int start, int middle, int end)
        {
            float cross;

            XY v1 = vector_gen(ref monotones, start, middle);
            XY v2 = vector_gen(ref monotones, middle, end);

            cross = (v1.x * v2.y) - (v1.y * v2.x);

            return cross;
        }

        // 선택정렬 함수
        static void selection_sort(ref List<XY> monotones)
        {
            monotones.Sort(delegate (XY A, XY B)
            {
                if (A.x > B.x) return 1;
                else if (A.x < B.x) return -1;
                else if (A.x == B.x)
                {
                    if (A.y > B.y) return 1;
                    else if (A.y < B.y) return -1;
                }
                return 0;
            });
        }

        // monotone 검사
        static List<XY> monotone_test(ref List<XY> monotones)
        {
            List<XY> chain = new List<XY>(monotones);
            List<XY> rev_chain = new List<XY>(monotones);
            rev_chain.Reverse();
            chain.AddRange(rev_chain);
            
            for (int i = 0; i < chain.Count; i++)
            {
                Console.WriteLine("chain"+ i + " : " + chain[i].x + ", " + chain[i].y);
            }

            int start = 0, middle = 1, end = 2;

            while (end < chain.Count)
            {
                float cross = cross_product(ref chain, start, middle, end);

                if (cross < 0)
                {
                    chain.RemoveAt(middle);
                }
                else
                {
                    start = middle;
                    middle = end;
                    end++;
                }
            }

            return chain;
        }
    }
}
