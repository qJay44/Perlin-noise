const canvas = document.querySelector('canvas');
const ctx = canvas.getContext('2d');

const w = canvas.width = innerWidth;
const h = canvas.height = innerHeight;

ctx.fillStyle = 'hsl(0, 0%, 7%)';
ctx.fillRect(0, 0, w, h);

const imgData = ctx.createImageData(w, h);
const data = imgData.data;
const brightArr = new Array(w * h);

// for (let x = 0; x < w; x++) {
//     for (let y = 0; y < h; y++) {

        
//         let bright = Math.floor(Math.random() * 255);

//         let pix = (x + y * w) * 4;
//         data[pix + 0] = bright;
//         data[pix + 1] = bright;
//         data[pix + 2] = bright;
//         data[pix + 3] = 255;

//         brightArr.push(bright);
//     }
// }

// ctx.putImageData(imgData, 0, 0);
function randBetween(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

class Perlin2D {
    constructor() {
        this.permutationTable = Array.from(new Uint8Array(1024).keys());
        this.rand = Math.random()
    }

    noise(x0, y0, i) {
        // upper left corner
        const int_x0 = Math.floor(x0);
        const int_y0 = Math.floor(y0);

        const local_x0 = x0 - int_x0;
        const local_y0 = y0 - int_y0;

        //              value0 + + + value1
        //                +            + 
        //                +            +
        //                +            + 
        //              value3 + + + value4

        topLeftGradient = getGradVector(int_x0, int_y0);

        let upper = lepr(value0, value1, local_x0);
        let lower = lepr(value3, value4, local_x0)

        let n = lepr(upper, lower, local_y0)
    }

    // linear interpolation
    lepr(a, b, t) {
        // a * (t - 1) + b * t
        return a + (b - a) * t;
    }

    getGradVector(x, y) {
        let v = Math.floor(((x * 1836311903) ^ (y * 2971215073) + 4807526976) & 1023);
        switch (vector) {
            case 0: return [1, 0];
            case 1: return [-1, 0];
            case 2: return [0, 1];
            case 3: return [0, -1];
        }
    }

    dotProduct(a, b) {
        return a[0] * b[0] + a[1] * b[1];
    }
}
