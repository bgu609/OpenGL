using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

namespace Monotone_Console
{
    class Program
    {
        //----------------------------------------------------- 샘플

        static List<float> sample_x = new List<float>() {
                0.28941f, 0.439397f, 0.515231f, -0.608676f, -0.719035f, -0.27297f, 0.39598f, -0.348569f, 0.338582f, -0.402379f,
                -0.356486f, -0.913199f, 0.00906308f, 0.76587f, 0.907783f, -0.0789068f, 0.106984f, 0.758958f, 0.315f, -0.170193f,
                -0.238396f, -0.610595f, 0.0526269f, 0.677162f, 0.26f, -0.153209f, -0.149909f, 0.325937f, -0.35105f, -0.620496f,
                -0.00866025f, -0.391086f, -0.608589f, 0.0146541f, 0.13906f, 0.0138919f, 0.423205f, -0.761151f, -0.319454f, -0.692108f,
                0.0644526f, -0.845723f, -0.529769f, -0.0398478f, 0.180611f, -0.385725f, -0.812215f, -0.0171034f, 0.679586f, 0.592006f,
                0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            };

        static List<float> sample_y = new List<float>() {
                0.111094f, -0.0230278f, -0.572222f, 0.197771f, 0.350697f, -0.454299f, 0.39598f, 0.536749f, 0.172516f, -0.431499f,
                0.240453f, 0.261855f, -0.00422618f, 0.26371f, 0.063478f, -0.161783f, 0.132115f, 0.0397753f, -0.545596f, -0.0586023f,
                -0.126757f, -0.381542f, -0.172135f, -0.40688f, -0.450333f, 0.128558f, -0.00523492f, 0.0516234f, -0.327359f, 0.520658f,
                -0.005f, -0.246922f, 0.365677f, 0.279616f, 0.231435f, 0.0787846f, -0.582492f, -0.277036f, 0.240726f, 0.198459f,
                0.303226f, 0.307818f, -0.281683f, 0.00348623f, 0.187028f, -0.231767f, 0.31178f, 0.979851f, -0.0237317f, 0.215473f,
                0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            };

        //static int MNT_NUM = 50;
        //-----------------------------------------------------

        static void Main(string[] args)
        {
            Convex_Hull(sample_x, sample_y, true);
        }

        // convex hull 함수
        static void Convex_Hull()
        {
            Stopwatch watch = new Stopwatch(); // 스탑워치
            int test_count = 50; // convex 검사 횟수
            bool close_chain = true; // 폐곡선 여부

            List<XY> monotones = new List<XY>(); // xy 리스트
            monotones = XY_extract(sample_x, sample_y); // 샘플 추출

            watch.Start(); // 시간 측정 시작
            list_sort(ref monotones); // 얻어진 monotones 정렬
            watch.Stop(); // 시간 측정 끝
            Console.WriteLine("List Sorting Time : " + watch.ElapsedMilliseconds + "ms\n");

            watch.Reset(); // 스탑워치 리셋

            watch.Start(); // 시간 측정 시작
            monotones = convex_test(ref monotones, close_chain, test_count); // convex 검사 후 정제된 monotones반환
            watch.Stop(); // 시간 측정 끝
            Console.WriteLine("Convex Test Time : " + watch.ElapsedMilliseconds + "ms\n");

            for (int j = 0; j < monotones.Count; j++)
            {
                Console.WriteLine("XY " + j + "\t:    " + monotones[j].x + "\t,    " + monotones[j].y);
            }
            Console.WriteLine("\n");
        }
        // convex hull 함수 (x 좌표 리스트, y 좌표 리스트, 폐곡선 여부), xy리스트 반환
        static List<XY> Convex_Hull(List<float> x_list, List<float> y_list, bool close_chain)
        {
            Stopwatch watch = new Stopwatch(); // 스탑워치
            int test_count = 50; // convex 검사 횟수

            List<XY> monotones = new List<XY>(); // xy 리스트
            monotones = XY_extract(x_list, y_list); // 샘플 추출

            watch.Start(); // 시간 측정 시작
            list_sort(ref monotones); // 얻어진 monotones 정렬
            watch.Stop(); // 시간 측정 끝
            Console.WriteLine("List Sorting Time : " + watch.ElapsedMilliseconds + "ms\n");

            watch.Reset(); // 스탑워치 리셋

            watch.Start(); // 시간 측정 시작
            monotones = convex_test(ref monotones, close_chain, test_count); // convex 검사 후 정제된 monotones반환
            watch.Stop(); // 시간 측정 끝
            Console.WriteLine("Convex Test Time : " + watch.ElapsedMilliseconds + "ms\n");

            for (int j = 0; j < monotones.Count; j++)
            {
                Console.WriteLine("XY " + j + "\t:    " + monotones[j].x + "\t,    " + monotones[j].y);
            }
            Console.WriteLine("\n");

            return monotones;
        }

        // 2차원 좌표 구조체
        struct XY
        {
            public float x;
            public float y;
        }

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

        // 좌표 추출 함수
        static List<XY> XY_extract()
        {
            XY insert; // 좌표 단위로 입력
            List<XY> extracts = new List<XY>();

            int num = sample_x.Count; // x, y 리스트 길이 같다는 가정 하

            for (int i = 0; i < num; i++)
            {
                insert.x = sample_x[i]; insert.y = sample_y[i]; // 샘플에서 좌표 추출
                extracts.Add(insert); // 좌표를 하나씩 입력
            }

            return extracts;
        }
        static List<XY> XY_extract(List<float> x_list, List<float> y_list)
        {
            XY insert; // 좌표 단위로 입력
            List<XY> extracts = new List<XY>();

            int num = x_list.Count; // x, y 리스트 길이 같다는 가정 하

            for (int i = 0; i < num; i++)
            {
                insert.x = x_list[i]; insert.y = y_list[i]; // 샘플에서 좌표 추출
                extracts.Add(insert); // 좌표를 하나씩 입력
            }

            return extracts;
        }

        // 리스트 정렬 함수
        static void list_sort(ref List<XY> monotones)
        {
            monotones = monotones.Distinct().ToList();

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

        // convex_test
        static List<XY> convex_test(ref List<XY> monotones, bool close_chain, int test_count)
        {
            // monotone chain 알고리즘에선 forward와 backward list를 따로 관리해야 함
            List<XY> chain = new List<XY>(monotones); // forward chain
            List<XY> rev_chain = new List<XY>(monotones); rev_chain.Reverse(); // backward chain

            convex_unit_test(ref chain, test_count); // forward chain 검사
            convex_unit_test(ref rev_chain, test_count); // backward chain 검사
            
            chain.AddRange(rev_chain); // 두 chain 연결
            if (!close_chain) // 개곡선 처리
            {
                chain.RemoveAt(chain.Count - 1);
            }

            return chain;
        }

        // convex_unit_test
        static void convex_unit_test(ref List<XY> chain, int test_count)
        {
            int start, middle, end;
            int break_checking;

            for (int i = 0; i < test_count; i++)
            {
                start = 0; middle = 1; end = 2;
                break_checking = chain.Count;

                while (end < chain.Count) // convex 검사
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

                if (break_checking == chain.Count) // convex 완성 체크
                {
                    Console.WriteLine("convex_unit_test : " + i + " times\n");
                    break;
                }
            }
        }
    }
}
