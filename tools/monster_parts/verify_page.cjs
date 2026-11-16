// Exercise the actual page script with a minimal DOM; does not replace a browser visual review.
const fs=require('fs'),vm=require('vm'),assert=require('assert');
const path=require('path'),root=path.resolve(__dirname,'../../output/monster-parts-all');
const html=fs.readFileSync(path.join(root,'index.html'),'utf8');
const source=html.match(/<script>([\s\S]*?)<\/script>/)[1];
class Element{constructor(){this.children=[];this.style={};this.value='';this.checked=false;this.textContent='';}append(...items){this.children.push(...items)}replaceChildren(...items){this.children=items}setAttribute(){}addEventListener(){}}
const ids=Object.fromEntries(['search','tier','variants','count','cards'].map(id=>[id,new Element()]));ids.tier.value='normal';
const document={getElementById:id=>ids[id],createElement:()=>new Element()};
const context=vm.createContext({document});vm.runInContext(source,context);
assert.equal(ids.cards.children.length,51);
ids.variants.checked=true;vm.runInContext('render()',context);assert.equal(ids.cards.children.length,357);
ids.search.value='c347';vm.runInContext('render()',context);assert.equal(ids.cards.children.length,1);
ids.tier.value='boss';vm.runInContext('render()',context);
let card=ids.cards.children[0];assert.equal(card.children[2].children.length,9);
card.children[2].children[0].onclick();assert(card.children[4].textContent.includes('CMF #'));
ids.search.value='does-not-exist';vm.runInContext('render()',context);assert.equal(ids.cards.children.length,0);
console.log('PASS: actual page script renders 51/357 entries; search, tier switching and block details work.');
