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
        this.permutation = [ 151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 
                      103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 
                      26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 
                      87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 
                      77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 
                      46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 
                      187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 
                      198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 
                      255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 
                      170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 
                      172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 
                      104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 
                      241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 
                      157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 
                      93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180 ];
    }

    getGradVector(x, y) {
        let v = Math.floor(((x * 1836311903) ^ (y * 2971215073) + 4807526976) & 1023);
        v = this.permutation[v] & 3;

        switch (v) {
            case 0: return [1, 0];
            case 1: return [-1, 0];
            case 2: return [0, 1];
            case 3: return [0, -1];
        }
    }

    qunticCurve(t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    // linear interpolation
    lepr(a, b, t) {
        return a + (b - a) * t;
    }

    dotProduct(a, b) {
        return a[0] * b[0] + a[1] * b[1];
    }

    noise(x, y) {
        // upper left corner
        const left = Math.floor(x);
        const top = Math.floor(y);
        let pointInQuadX = x - left;
        let pointInQuadY = y - top;

        //              TL + + + TR
        //              +         + 
        //              +         +
        //              +         + 
        //              BL + + + BR

        const topLeftGrad = this.getGradVector(left, top);
        const topRightGrad = this.getGradVector(left + 1, top);
        const bottomLeftGrad = this.getGradVector(left, top + 1);
        const bottomRightGrad = this.getGradVector(left + 1, top + 1);

        const disTopLeft = [pointInQuadX, pointInQuadY];
        const disTopRight = [pointInQuadX - 1, pointInQuadY];
        const disBottomLeft = [pointInQuadX, pointInQuadY - 1];
        const disBottomRight = [pointInQuadX - 1, pointInQuadY - 1];

        const tx1 = this.dotProduct(disTopLeft, topLeftGrad);
        const tx2 = this.dotProduct(disTopRight, topRightGrad);
        const bx1 = this.dotProduct(disBottomLeft, bottomLeftGrad);
        const bx2 = this.dotProduct(disBottomRight, bottomRightGrad);

        pointInQuadX = this.qunticCurve(pointInQuadX);
        pointInQuadY = this.qunticCurve(pointInQuadY);

        const tx = this.lepr(tx1, tx2, pointInQuadX);
        const bx = this.lepr(bx1, bx2, pointInQuadX);
        const tb = this.lepr(tx, bx, pointInQuadY);

        return tb;
    }
}

let n = new Perlin2D();
for (let index = 0; index < 1000; index++) {
    n.noise(29, index);
}

