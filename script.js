const canvas = document.querySelector('canvas');
const ctx = canvas.getContext('2d');

const w = canvas.width = innerWidth;
const h = canvas.height = innerHeight;

function draw() {
    ctx.fillStyle = 'hsl(0, 0%, 7%)';
    ctx.fillRect(0, 0, w, h);

    ctx.beginPath();
    ctx.fillStyle = 'white';
    ctx.arc(0, h / 2, 24, 0, Math.PI * 2);
    ctx.fill();
    ctx.closePath();

    requestAnimationFrame(draw);
}

function perlinNoise(x, y) {
    const x0 = Math.floor(x);
    const x1 = x0 + 1;
    const y0 = Math.floor(y);
    const y1 = y0 + 1;

    const sx = x - x0;
    const sy = y - y0;

    let n0, n1, ix0, ix1;

    n0 = dotGridGradient(x0, y0, x, y);
    n1 = dotGridGradient(x1, y0, x, y);
    ix0 = interpolate(n0, n1, sx);
    
    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    ix1 = interpolate(n0, n1, sx);

    return interpolate(ix0, ix1, sy);
}

function dotGridGradient(ix, iy, x, y) {
    const dx = x - ix;
    const dy = y - iy;

    return dx * Math.random() + dy * Math.random();
}

function interpolate(edge0, edge1, x) {
    x = clamp((x - edge0) / (edge1 - edge0), 0, 1);

    return 6 * x ** 5 - 15 * x ** 4 + 10 * x ** 3;
}

function clamp(x, lowerLimit, upperLimit) {
    x = x < lowerLimit ? lowerLimit : x;
    x = x > upperLimit ? upperLimit : x;

    return x;
}

draw();

let iiii = perlinNoise(2, 2)
console.log(iiii);