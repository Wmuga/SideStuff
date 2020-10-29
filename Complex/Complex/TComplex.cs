using System;
using System.Runtime.CompilerServices;

namespace Complex
{
    public class TComplex
    {
        private double im;
        private double real;

        public TComplex()
        {
            im = 0;
            real = 0;
        }

        public TComplex(double real, double im)
        {
            this.im = im;
            this.real = real;
        }

        public static TComplex operator +(TComplex a) => a;
        public static TComplex operator -(TComplex a) => new TComplex(-a.real, -a.im);

        public static TComplex operator +(TComplex l, TComplex r) => new TComplex(l.real + r.real, l.im + r.im);
        public static TComplex operator +(TComplex l, double r) => new TComplex(l.real + r, l.im);

        public static TComplex operator -(TComplex l, TComplex r) => new TComplex(l.real - r.real, l.im - r.im);
        public static TComplex operator -(TComplex l, double r) => new TComplex(l.real - r, l.im);

        public static TComplex operator *(TComplex l, TComplex r) =>
            new TComplex(l.real * r.real - l.im * r.im, l.im * r.real + l.real * r.im);

        public static TComplex operator *(TComplex l, double r) => new TComplex(l.real * r, l.im * r);

        public static TComplex operator /(TComplex l, TComplex r) =>
            l * (new TComplex(r.real, -r.im)) / (r.real * r.real + r.im * r.im);

        public static TComplex operator /(TComplex l, double r) => new TComplex(l.real / r, l.im / r);

        public string GetAlg()
        {
            string res = real + " ";

            if (im != 0)
            {
                if (im > 0) res += "+ j" + im;
                else res += "- j" + Math.Abs(im);
            }

            return res;
        }

        public string GetPolar()
        {
            string res = Math.Sqrt(real*real+im*im) + " e{ ";
            if (real == 0)
            {
                if (im<0) res+="-";
                res += "90";
            }
            else
            {
                double angle = Math.Atan(im / real)*180/Math.PI;
                if (im < 0 && real < 0) angle -= 180;
                if (im > 0 && real < 0) angle += 180;
                res += angle;
            }

            return res+" }";
        }
    }
}