<div class="markdown prose w-full break-words dark:prose-invert dark">
    <p>要理解为什么构建一个最小二叉堆的时间复杂度是 <span class="katex"><span class="katex-mathml"><math
                    xmlns="http://www.w3.org/1998/Math/MathML">
                    <semantics>
                        <mrow>
                            <mi>O</mi>
                            <mo stretchy="false">(</mo>
                            <mi>V</mi>
                            <mo stretchy="false">)</mo>
                        </mrow>
                        <annotation encoding="application/x-tex">O(V)</annotation>
                    </semantics>
                </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                        style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                        style="margin-right: 0.02778em;">O</span><span class="mopen">(</span><span
                        class="mord mathnormal" style="margin-right: 0.22222em;">V</span><span
                        class="mclose">)</span></span></span></span>，我们需要详细分析各个层级节点的下滤操作成本。</p>
    <h3>1. 堆的基本结构</h3>
    <ul>
        <li>一个完全二叉堆的节点总数为 <span class="katex"><span class="katex-mathml"><math
                        xmlns="http://www.w3.org/1998/Math/MathML">
                        <semantics>
                            <mrow>
                                <mi>V</mi>
                            </mrow>
                            <annotation encoding="application/x-tex">V</annotation>
                        </semantics>
                    </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                            style="height: 0.6833em;"></span><span class="mord mathnormal"
                            style="margin-right: 0.22222em;">V</span></span></span></span>，其中有大约 <span
                class="katex"><span class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML">
                        <semantics>
                            <mrow>
                                <mi>V</mi>
                                <mi mathvariant="normal">/</mi>
                                <mn>2</mn>
                            </mrow>
                            <annotation encoding="application/x-tex">V/2</annotation>
                        </semantics>
                    </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                            style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                            style="margin-right: 0.22222em;">V</span><span class="mord">/2</span></span></span></span>
            个叶子节点（高度为 0，不需要进行下滤操作）。</li>
        <li>二叉堆的高度为 <span class="katex"><span class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML">
                        <semantics>
                            <mrow>
                                <mi>log</mi>
                                <mo>⁡</mo>
                                <mi>V</mi>
                            </mrow>
                            <annotation encoding="application/x-tex">\log V</annotation>
                        </semantics>
                    </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                            style="height: 0.8889em; vertical-align: -0.1944em;"></span><span class="mop">lo<span
                                style="margin-right: 0.01389em;">g</span></span><span class="mspace"
                            style="margin-right: 0.1667em;"></span><span class="mord mathnormal"
                            style="margin-right: 0.22222em;">V</span></span></span></span>，每一层的节点数和高度有如下规律：</li>
    </ul>
    <table>
        <thead>
            <tr>
                <th style="text-align: center;">层级（从根到叶）</th>
                <th style="text-align: center;">节点数</th>
                <th style="text-align: center;">节点的高度</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td>0</td>
                <td>1</td>
                <td><span class="katex"><span class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML">
                                <semantics>
                                    <mrow>
                                        <mi>log</mi>
                                        <mo>⁡</mo>
                                        <mi>V</mi>
                                    </mrow>
                                    <annotation encoding="application/x-tex">\log V</annotation>
                                </semantics>
                            </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span
                                    class="strut" style="height: 0.8889em; vertical-align: -0.1944em;"></span><span
                                    class="mop">lo<span style="margin-right: 0.01389em;">g</span></span><span
                                    class="mspace" style="margin-right: 0.1667em;"></span><span class="mord mathnormal"
                                    style="margin-right: 0.22222em;">V</span></span></span></span></td>
            </tr>
            <tr>
                <td>1</td>
                <td>2</td>
                <td><span class="katex"><span class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML">
                                <semantics>
                                    <mrow>
                                        <mi>log</mi>
                                        <mo>⁡</mo>
                                        <mi>V</mi>
                                        <mo>−</mo>
                                        <mn>1</mn>
                                    </mrow>
                                    <annotation encoding="application/x-tex">\log V - 1</annotation>
                                </semantics>
                            </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span
                                    class="strut" style="height: 0.8889em; vertical-align: -0.1944em;"></span><span
                                    class="mop">lo<span style="margin-right: 0.01389em;">g</span></span><span
                                    class="mspace" style="margin-right: 0.1667em;"></span><span class="mord mathnormal"
                                    style="margin-right: 0.22222em;">V</span><span class="mspace"
                                    style="margin-right: 0.2222em;"></span><span class="mbin">−</span><span
                                    class="mspace" style="margin-right: 0.2222em;"></span></span><span
                                class="base"><span class="strut" style="height: 0.6444em;"></span><span
                                    class="mord">1</span></span></span></span></td>
            </tr>
            <tr>
                <td>2</td>
                <td>4</td>
                <td><span class="katex"><span class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML">
                                <semantics>
                                    <mrow>
                                        <mi>log</mi>
                                        <mo>⁡</mo>
                                        <mi>V</mi>
                                        <mo>−</mo>
                                        <mn>2</mn>
                                    </mrow>
                                    <annotation encoding="application/x-tex">\log V - 2</annotation>
                                </semantics>
                            </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span
                                    class="strut" style="height: 0.8889em; vertical-align: -0.1944em;"></span><span
                                    class="mop">lo<span style="margin-right: 0.01389em;">g</span></span><span
                                    class="mspace" style="margin-right: 0.1667em;"></span><span class="mord mathnormal"
                                    style="margin-right: 0.22222em;">V</span><span class="mspace"
                                    style="margin-right: 0.2222em;"></span><span class="mbin">−</span><span
                                    class="mspace" style="margin-right: 0.2222em;"></span></span><span
                                class="base"><span class="strut" style="height: 0.6444em;"></span><span
                                    class="mord">2</span></span></span></span></td>
            </tr>
            <tr>
                <td>3</td>
                <td>8</td>
                <td><span class="katex"><span class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML">
                                <semantics>
                                    <mrow>
                                        <mi>log</mi>
                                        <mo>⁡</mo>
                                        <mi>V</mi>
                                        <mo>−</mo>
                                        <mn>3</mn>
                                    </mrow>
                                    <annotation encoding="application/x-tex">\log V - 3</annotation>
                                </semantics>
                            </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span
                                    class="strut" style="height: 0.8889em; vertical-align: -0.1944em;"></span><span
                                    class="mop">lo<span style="margin-right: 0.01389em;">g</span></span><span
                                    class="mspace" style="margin-right: 0.1667em;"></span><span class="mord mathnormal"
                                    style="margin-right: 0.22222em;">V</span><span class="mspace"
                                    style="margin-right: 0.2222em;"></span><span class="mbin">−</span><span
                                    class="mspace" style="margin-right: 0.2222em;"></span></span><span
                                class="base"><span class="strut" style="height: 0.6444em;"></span><span
                                    class="mord">3</span></span></span></span></td>
            </tr>
            <tr>
                <td>...</td>
                <td>...</td>
                <td>...</td>
            </tr>
            <tr>
                <td><span class="katex"><span class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML">
                                <semantics>
                                    <mrow>
                                        <mi>h</mi>
                                    </mrow>
                                    <annotation encoding="application/x-tex">h</annotation>
                                </semantics>
                            </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span
                                    class="strut" style="height: 0.6944em;"></span><span
                                    class="mord mathnormal">h</span></span></span></span></td>
                <td><span class="katex"><span class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML">
                                <semantics>
                                    <mrow>
                                        <msup>
                                            <mn>2</mn>
                                            <mi>h</mi>
                                        </msup>
                                    </mrow>
                                    <annotation encoding="application/x-tex">2^h</annotation>
                                </semantics>
                            </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span
                                    class="strut" style="height: 0.8491em;"></span><span class="mord"><span
                                        class="mord">2</span><span class="msupsub"><span class="vlist-t"><span
                                                class="vlist-r"><span class="vlist" style="height: 0.8491em;"><span
                                                        style="top: -3.063em; margin-right: 0.05em;"><span
                                                            class="pstrut" style="height: 2.7em;"></span><span
                                                            class="sizing reset-size6 size3 mtight"><span
                                                                class="mord mathnormal mtight">h</span></span></span></span></span></span></span></span></span></span></span>
                </td>
                <td><span class="katex"><span class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML">
                                <semantics>
                                    <mrow>
                                        <mn>0</mn>
                                    </mrow>
                                    <annotation encoding="application/x-tex">0</annotation>
                                </semantics>
                            </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span
                                    class="strut" style="height: 0.6444em;"></span><span
                                    class="mord">0</span></span></span></span></td>
            </tr>
        </tbody>
    </table>
    <h3>2. 下滤的代价</h3>
    <p>在堆的构建过程中，"下滤"操作的代价与节点的高度成正比。越接近堆底部的节点，其下滤需要的步数越少，而越接近顶部的节点，可能需要执行更多的下滤操作。</p>
    <p>具体地：</p>
    <ul>
        <li>叶子节点（高度为 0）的下滤操作代价为 0，因为它们不需要进行任何调整。</li>
        <li>倒数第二层节点（高度为 1）的下滤代价为 1。</li>
        <li>第三层节点（高度为 2）的下滤代价为 2，依此类推。</li>
    </ul>
    <h4>各层的下滤操作总代价计算</h4>
    <p>我们可以通过层级来总结各层的节点数及其对应的下滤成本。</p>
    <ul>
        <li><strong>高度为 0 的节点数</strong>：叶节点，大约为 <span class="katex"><span class="katex-mathml"><math
                        xmlns="http://www.w3.org/1998/Math/MathML">
                        <semantics>
                            <mrow>
                                <mi>V</mi>
                                <mi mathvariant="normal">/</mi>
                                <mn>2</mn>
                            </mrow>
                            <annotation encoding="application/x-tex">V/2</annotation>
                        </semantics>
                    </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                            style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                            style="margin-right: 0.22222em;">V</span><span
                            class="mord">/2</span></span></span></span>，无需下滤，因此总成本为 <span class="katex"><span
                    class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML">
                        <semantics>
                            <mrow>
                                <mi>V</mi>
                                <mi mathvariant="normal">/</mi>
                                <mn>2</mn>
                                <mo>×</mo>
                                <mn>0</mn>
                                <mo>=</mo>
                                <mn>0</mn>
                            </mrow>
                            <annotation encoding="application/x-tex">V/2 \times 0 = 0</annotation>
                        </semantics>
                    </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                            style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                            style="margin-right: 0.22222em;">V</span><span class="mord">/2</span><span class="mspace"
                            style="margin-right: 0.2222em;"></span><span class="mbin">×</span><span class="mspace"
                            style="margin-right: 0.2222em;"></span></span><span class="base"><span class="strut"
                            style="height: 0.6444em;"></span><span class="mord">0</span><span class="mspace"
                            style="margin-right: 0.2778em;"></span><span class="mrel">=</span><span class="mspace"
                            style="margin-right: 0.2778em;"></span></span><span class="base"><span class="strut"
                            style="height: 0.6444em;"></span><span class="mord">0</span></span></span></span>。</li>
        <li><strong>高度为 1 的节点数</strong>：约为 <span class="katex"><span class="katex-mathml"><math
                        xmlns="http://www.w3.org/1998/Math/MathML">
                        <semantics>
                            <mrow>
                                <mi>V</mi>
                                <mi mathvariant="normal">/</mi>
                                <mn>4</mn>
                            </mrow>
                            <annotation encoding="application/x-tex">V/4</annotation>
                        </semantics>
                    </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                            style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                            style="margin-right: 0.22222em;">V</span><span
                            class="mord">/4</span></span></span></span>，每个节点下滤 1 次，总成本为 <span class="katex"><span
                    class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML">
                        <semantics>
                            <mrow>
                                <mi>V</mi>
                                <mi mathvariant="normal">/</mi>
                                <mn>4</mn>
                                <mo>×</mo>
                                <mn>1</mn>
                                <mo>=</mo>
                                <mi>V</mi>
                                <mi mathvariant="normal">/</mi>
                                <mn>4</mn>
                            </mrow>
                            <annotation encoding="application/x-tex">V/4 \times 1 = V/4</annotation>
                        </semantics>
                    </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                            style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                            style="margin-right: 0.22222em;">V</span><span class="mord">/4</span><span class="mspace"
                            style="margin-right: 0.2222em;"></span><span class="mbin">×</span><span class="mspace"
                            style="margin-right: 0.2222em;"></span></span><span class="base"><span class="strut"
                            style="height: 0.6444em;"></span><span class="mord">1</span><span class="mspace"
                            style="margin-right: 0.2778em;"></span><span class="mrel">=</span><span class="mspace"
                            style="margin-right: 0.2778em;"></span></span><span class="base"><span class="strut"
                            style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                            style="margin-right: 0.22222em;">V</span><span class="mord">/4</span></span></span></span>。
        </li>
        <li><strong>高度为 2 的节点数</strong>：约为 <span class="katex"><span class="katex-mathml"><math
                        xmlns="http://www.w3.org/1998/Math/MathML">
                        <semantics>
                            <mrow>
                                <mi>V</mi>
                                <mi mathvariant="normal">/</mi>
                                <mn>8</mn>
                            </mrow>
                            <annotation encoding="application/x-tex">V/8</annotation>
                        </semantics>
                    </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                            style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                            style="margin-right: 0.22222em;">V</span><span
                            class="mord">/8</span></span></span></span>，每个节点下滤 2 次，总成本为 <span class="katex"><span
                    class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML">
                        <semantics>
                            <mrow>
                                <mi>V</mi>
                                <mi mathvariant="normal">/</mi>
                                <mn>8</mn>
                                <mo>×</mo>
                                <mn>2</mn>
                                <mo>=</mo>
                                <mi>V</mi>
                                <mi mathvariant="normal">/</mi>
                                <mn>4</mn>
                            </mrow>
                            <annotation encoding="application/x-tex">V/8 \times 2 = V/4</annotation>
                        </semantics>
                    </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                            style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                            style="margin-right: 0.22222em;">V</span><span class="mord">/8</span><span class="mspace"
                            style="margin-right: 0.2222em;"></span><span class="mbin">×</span><span class="mspace"
                            style="margin-right: 0.2222em;"></span></span><span class="base"><span class="strut"
                            style="height: 0.6444em;"></span><span class="mord">2</span><span class="mspace"
                            style="margin-right: 0.2778em;"></span><span class="mrel">=</span><span class="mspace"
                            style="margin-right: 0.2778em;"></span></span><span class="base"><span class="strut"
                            style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                            style="margin-right: 0.22222em;">V</span><span class="mord">/4</span></span></span></span>。
        </li>
        <li><strong>高度为 3 的节点数</strong>：约为 <span class="katex"><span class="katex-mathml"><math
                        xmlns="http://www.w3.org/1998/Math/MathML">
                        <semantics>
                            <mrow>
                                <mi>V</mi>
                                <mi mathvariant="normal">/</mi>
                                <mn>16</mn>
                            </mrow>
                            <annotation encoding="application/x-tex">V/16</annotation>
                        </semantics>
                    </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                            style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                            style="margin-right: 0.22222em;">V</span><span
                            class="mord">/16</span></span></span></span>，每个节点下滤 3 次，总成本为 <span class="katex"><span
                    class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML">
                        <semantics>
                            <mrow>
                                <mi>V</mi>
                                <mi mathvariant="normal">/</mi>
                                <mn>16</mn>
                                <mo>×</mo>
                                <mn>3</mn>
                                <mo>=</mo>
                                <mn>3</mn>
                                <mi>V</mi>
                                <mi mathvariant="normal">/</mi>
                                <mn>16</mn>
                            </mrow>
                            <annotation encoding="application/x-tex">V/16 \times 3 = 3V/16</annotation>
                        </semantics>
                    </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                            style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                            style="margin-right: 0.22222em;">V</span><span class="mord">/16</span><span class="mspace"
                            style="margin-right: 0.2222em;"></span><span class="mbin">×</span><span class="mspace"
                            style="margin-right: 0.2222em;"></span></span><span class="base"><span class="strut"
                            style="height: 0.6444em;"></span><span class="mord">3</span><span class="mspace"
                            style="margin-right: 0.2778em;"></span><span class="mrel">=</span><span class="mspace"
                            style="margin-right: 0.2778em;"></span></span><span class="base"><span class="strut"
                            style="height: 1em; vertical-align: -0.25em;"></span><span class="mord">3</span><span
                            class="mord mathnormal" style="margin-right: 0.22222em;">V</span><span
                            class="mord">/16</span></span></span></span>。</li>
        <li><strong>依此类推</strong>，直到根节点。</li>
    </ul>
    <h3>3. 总成本计算</h3>
    <p>总成本是所有层下滤操作成本的和：</p><span class="katex-display"><span class="katex"><span class="katex-mathml"><math
                    xmlns="http://www.w3.org/1998/Math/MathML" display="block">
                    <semantics>
                        <mrow>
                            <mi>T</mi>
                            <mo stretchy="false">(</mo>
                            <mi>V</mi>
                            <mo stretchy="false">)</mo>
                            <mo>=</mo>
                            <munderover>
                                <mo>∑</mo>
                                <mrow>
                                    <mi>i</mi>
                                    <mo>=</mo>
                                    <mn>0</mn>
                                </mrow>
                                <mrow>
                                    <mi>log</mi>
                                    <mo>⁡</mo>
                                    <mi>V</mi>
                                </mrow>
                            </munderover>
                            <mrow>
                                <mo fence="true">(</mo>
                                <mtext>第&nbsp;</mtext>
                                <mi>i</mi>
                                <mtext>&nbsp;层的节点数</mtext>
                                <mo>×</mo>
                                <mtext>下滤成本</mtext>
                                <mo fence="true">)</mo>
                            </mrow>
                        </mrow>
                        <annotation encoding="application/x-tex">T(V) = \sum_{i=0}^{\log V} \left( \text{第 } i \text{
                            层的节点数} \times \text{下滤成本} \right)</annotation>
                    </semantics>
                </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                        style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                        style="margin-right: 0.13889em;">T</span><span class="mopen">(</span><span
                        class="mord mathnormal" style="margin-right: 0.22222em;">V</span><span
                        class="mclose">)</span><span class="mspace" style="margin-right: 0.2778em;"></span><span
                        class="mrel">=</span><span class="mspace" style="margin-right: 0.2778em;"></span></span><span
                    class="base"><span class="strut" style="height: 3.1609em; vertical-align: -1.2777em;"></span><span
                        class="mop op-limits"><span class="vlist-t vlist-t2"><span class="vlist-r"><span class="vlist"
                                    style="height: 1.8832em;"><span style="top: -1.8723em; margin-left: 0em;"><span
                                            class="pstrut" style="height: 3.05em;"></span><span
                                            class="sizing reset-size6 size3 mtight"><span class="mord mtight"><span
                                                    class="mord mathnormal mtight">i</span><span
                                                    class="mrel mtight">=</span><span
                                                    class="mord mtight">0</span></span></span></span><span
                                        style="top: -3.05em;"><span class="pstrut"
                                            style="height: 3.05em;"></span><span><span
                                                class="mop op-symbol large-op">∑</span></span></span><span
                                        style="top: -4.3471em; margin-left: 0em;"><span class="pstrut"
                                            style="height: 3.05em;"></span><span
                                            class="sizing reset-size6 size3 mtight"><span class="mord mtight"><span
                                                    class="mop mtight"><span class="mtight">l</span><span
                                                        class="mtight">o</span><span class="mtight"
                                                        style="margin-right: 0.01389em;">g</span></span><span
                                                    class="mspace mtight" style="margin-right: 0.1952em;"></span><span
                                                    class="mord mathnormal mtight"
                                                    style="margin-right: 0.22222em;">V</span></span></span></span></span><span
                                    class="vlist-s">​</span></span><span class="vlist-r"><span class="vlist"
                                    style="height: 1.2777em;"><span></span></span></span></span></span><span
                        class="mspace" style="margin-right: 0.1667em;"></span><span class="minner"><span
                            class="mopen delimcenter" style="top: 0em;">(</span><span class="mord text"><span
                                class="mord cjk_fallback">第</span><span class="mord">&nbsp;</span></span><span
                            class="mord mathnormal">i</span><span class="mord text"><span
                                class="mord">&nbsp;</span><span class="mord cjk_fallback">层的节点数</span></span><span
                            class="mspace" style="margin-right: 0.2222em;"></span><span class="mbin">×</span><span
                            class="mspace" style="margin-right: 0.2222em;"></span><span class="mord text"><span
                                class="mord cjk_fallback">下滤成本</span></span><span class="mclose delimcenter"
                            style="top: 0em;">)</span></span></span></span></span></span>
    <span class="katex-display" ><span class="katex"><span class="katex-mathml"><math
                    xmlns="http://www.w3.org/1998/Math/MathML" display="block">
                    <semantics>
                        <mrow>
                            <mi>T</mi>
                            <mo stretchy="false">(</mo>
                            <mi>V</mi>
                            <mo stretchy="false">)</mo>
                            <mo>=</mo>
                            <mrow>
                                <mo fence="true">(</mo>
                                <mi>V</mi>
                                <mi mathvariant="normal">/</mi>
                                <mn>2</mn>
                                <mo>×</mo>
                                <mn>0</mn>
                                <mo fence="true">)</mo>
                            </mrow>
                            <mo>+</mo>
                            <mrow>
                                <mo fence="true">(</mo>
                                <mi>V</mi>
                                <mi mathvariant="normal">/</mi>
                                <mn>4</mn>
                                <mo>×</mo>
                                <mn>1</mn>
                                <mo fence="true">)</mo>
                            </mrow>
                            <mo>+</mo>
                            <mrow>
                                <mo fence="true">(</mo>
                                <mi>V</mi>
                                <mi mathvariant="normal">/</mi>
                                <mn>8</mn>
                                <mo>×</mo>
                                <mn>2</mn>
                                <mo fence="true">)</mo>
                            </mrow>
                            <mo>+</mo>
                            <mrow>
                                <mo fence="true">(</mo>
                                <mi>V</mi>
                                <mi mathvariant="normal">/</mi>
                                <mn>16</mn>
                                <mo>×</mo>
                                <mn>3</mn>
                                <mo fence="true">)</mo>
                            </mrow>
                            <mo>+</mo>
                            <mo>⋯</mo>
                            <mo>+</mo>
                            <mrow>
                                <mo fence="true">(</mo>
                                <mn>1</mn>
                                <mo>×</mo>
                                <mi>log</mi>
                                <mo>⁡</mo>
                                <mi>V</mi>
                                <mo fence="true">)</mo>
                            </mrow>
                        </mrow>
                        <annotation encoding="application/x-tex">T(V) = \left( V/2 \times 0 \right) + \left( V/4 \times
                            1 \right) + \left( V/8 \times 2 \right) + \left( V/16 \times 3 \right) + \cdots + \left( 1
                            \times \log V \right)</annotation>
                    </semantics>
                </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                        style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                        style="margin-right: 0.13889em;">T</span><span class="mopen">(</span><span
                        class="mord mathnormal" style="margin-right: 0.22222em;">V</span><span
                        class="mclose">)</span><span class="mspace" style="margin-right: 0.2778em;"></span><span
                        class="mrel">=</span><span class="mspace" style="margin-right: 0.2778em;"></span></span><span
                    class="base"><span class="strut" style="height: 1em; vertical-align: -0.25em;"></span><span
                        class="minner"><span class="mopen delimcenter" style="top: 0em;">(</span><span
                            class="mord mathnormal" style="margin-right: 0.22222em;">V</span><span
                            class="mord">/2</span><span class="mspace" style="margin-right: 0.2222em;"></span><span
                            class="mbin">×</span><span class="mspace" style="margin-right: 0.2222em;"></span><span
                            class="mord">0</span><span class="mclose delimcenter" style="top: 0em;">)</span></span><span
                        class="mspace" style="margin-right: 0.2222em;"></span><span class="mbin">+</span><span
                        class="mspace" style="margin-right: 0.2222em;"></span></span><span class="base"><span
                        class="strut" style="height: 1em; vertical-align: -0.25em;"></span><span class="minner"><span
                            class="mopen delimcenter" style="top: 0em;">(</span><span class="mord mathnormal"
                            style="margin-right: 0.22222em;">V</span><span class="mord">/4</span><span class="mspace"
                            style="margin-right: 0.2222em;"></span><span class="mbin">×</span><span class="mspace"
                            style="margin-right: 0.2222em;"></span><span class="mord">1</span><span
                            class="mclose delimcenter" style="top: 0em;">)</span></span><span class="mspace"
                        style="margin-right: 0.2222em;"></span><span class="mbin">+</span><span class="mspace"
                        style="margin-right: 0.2222em;"></span></span><span class="base"><span class="strut"
                        style="height: 1em; vertical-align: -0.25em;"></span><span class="minner"><span
                            class="mopen delimcenter" style="top: 0em;">(</span><span class="mord mathnormal"
                            style="margin-right: 0.22222em;">V</span><span class="mord">/8</span><span class="mspace"
                            style="margin-right: 0.2222em;"></span><span class="mbin">×</span><span class="mspace"
                            style="margin-right: 0.2222em;"></span><span class="mord">2</span><span
                            class="mclose delimcenter" style="top: 0em;">)</span></span><span class="mspace"
                        style="margin-right: 0.2222em;"></span><span class="mbin">+</span><span class="mspace"
                        style="margin-right: 0.2222em;"></span></span><span class="base"><span class="strut"
                        style="height: 1em; vertical-align: -0.25em;"></span><span class="minner"><span
                            class="mopen delimcenter" style="top: 0em;">(</span><span class="mord mathnormal"
                            style="margin-right: 0.22222em;">V</span><span class="mord">/16</span><span class="mspace"
                            style="margin-right: 0.2222em;"></span><span class="mbin">×</span><span class="mspace"
                            style="margin-right: 0.2222em;"></span><span class="mord">3</span><span
                            class="mclose delimcenter" style="top: 0em;">)</span></span><span class="mspace"
                        style="margin-right: 0.2222em;"></span><span class="mbin">+</span><span class="mspace"
                        style="margin-right: 0.2222em;"></span></span><span class="base"><span class="strut"
                        style="height: 0.6667em; vertical-align: -0.0833em;"></span><span class="minner">⋯</span><span
                        class="mspace" style="margin-right: 0.2222em;"></span><span class="mbin">+</span><span
                        class="mspace" style="margin-right: 0.2222em;"></span></span><span class="base"><span
                        class="strut" style="height: 1em; vertical-align: -0.25em;"></span><span class="minner"><span
                            class="mopen delimcenter" style="top: 0em;">(</span><span class="mord">1</span><span
                            class="mspace" style="margin-right: 0.2222em;"></span><span class="mbin">×</span><span
                            class="mspace" style="margin-right: 0.2222em;"></span><span class="mop">lo<span
                                style="margin-right: 0.01389em;">g</span></span><span class="mspace"
                            style="margin-right: 0.1667em;"></span><span class="mord mathnormal"
                            style="margin-right: 0.22222em;">V</span><span class="mclose delimcenter"
                            style="top: 0em;">)</span></span></span></span></span></span>
    <p>简化表达：</p><span class="katex-display" ><span class="katex"><span class="katex-mathml"><math
                    xmlns="http://www.w3.org/1998/Math/MathML" display="block">
                    <semantics>
                        <mrow>
                            <mi>T</mi>
                            <mo stretchy="false">(</mo>
                            <mi>V</mi>
                            <mo stretchy="false">)</mo>
                            <mo>=</mo>
                            <munderover>
                                <mo>∑</mo>
                                <mrow>
                                    <mi>i</mi>
                                    <mo>=</mo>
                                    <mn>1</mn>
                                </mrow>
                                <mrow>
                                    <mi>log</mi>
                                    <mo>⁡</mo>
                                    <mi>V</mi>
                                </mrow>
                            </munderover>
                            <mfrac>
                                <mi>V</mi>
                                <msup>
                                    <mn>2</mn>
                                    <mi>i</mi>
                                </msup>
                            </mfrac>
                            <mo>×</mo>
                            <mi>i</mi>
                        </mrow>
                        <annotation encoding="application/x-tex">T(V) = \sum_{i=1}^{\log V} \frac{V}{2^i} \times i
                        </annotation>
                    </semantics>
                </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                        style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                        style="margin-right: 0.13889em;">T</span><span class="mopen">(</span><span
                        class="mord mathnormal" style="margin-right: 0.22222em;">V</span><span
                        class="mclose">)</span><span class="mspace" style="margin-right: 0.2778em;"></span><span
                        class="mrel">=</span><span class="mspace" style="margin-right: 0.2778em;"></span></span><span
                    class="base"><span class="strut" style="height: 3.1609em; vertical-align: -1.2777em;"></span><span
                        class="mop op-limits"><span class="vlist-t vlist-t2"><span class="vlist-r"><span class="vlist"
                                    style="height: 1.8832em;"><span style="top: -1.8723em; margin-left: 0em;"><span
                                            class="pstrut" style="height: 3.05em;"></span><span
                                            class="sizing reset-size6 size3 mtight"><span class="mord mtight"><span
                                                    class="mord mathnormal mtight">i</span><span
                                                    class="mrel mtight">=</span><span
                                                    class="mord mtight">1</span></span></span></span><span
                                        style="top: -3.05em;"><span class="pstrut"
                                            style="height: 3.05em;"></span><span><span
                                                class="mop op-symbol large-op">∑</span></span></span><span
                                        style="top: -4.3471em; margin-left: 0em;"><span class="pstrut"
                                            style="height: 3.05em;"></span><span
                                            class="sizing reset-size6 size3 mtight"><span class="mord mtight"><span
                                                    class="mop mtight"><span class="mtight">l</span><span
                                                        class="mtight">o</span><span class="mtight"
                                                        style="margin-right: 0.01389em;">g</span></span><span
                                                    class="mspace mtight" style="margin-right: 0.1952em;"></span><span
                                                    class="mord mathnormal mtight"
                                                    style="margin-right: 0.22222em;">V</span></span></span></span></span><span
                                    class="vlist-s">​</span></span><span class="vlist-r"><span class="vlist"
                                    style="height: 1.2777em;"><span></span></span></span></span></span><span
                        class="mspace" style="margin-right: 0.1667em;"></span><span class="mord"><span
                            class="mopen nulldelimiter"></span><span class="mfrac"><span class="vlist-t vlist-t2"><span
                                    class="vlist-r"><span class="vlist" style="height: 1.3603em;"><span
                                            style="top: -2.314em;"><span class="pstrut"
                                                style="height: 3em;"></span><span class="mord"><span class="mord"><span
                                                        class="mord">2</span><span class="msupsub"><span
                                                            class="vlist-t"><span class="vlist-r"><span class="vlist"
                                                                    style="height: 0.7507em;"><span
                                                                        style="top: -2.989em; margin-right: 0.05em;"><span
                                                                            class="pstrut"
                                                                            style="height: 2.7em;"></span><span
                                                                            class="sizing reset-size6 size3 mtight"><span
                                                                                class="mord mathnormal mtight">i</span></span></span></span></span></span></span></span></span></span><span
                                            style="top: -3.23em;"><span class="pstrut" style="height: 3em;"></span><span
                                                class="frac-line"
                                                style="border-bottom-width: 0.04em;"></span></span><span
                                            style="top: -3.677em;"><span class="pstrut"
                                                style="height: 3em;"></span><span class="mord"><span
                                                    class="mord mathnormal"
                                                    style="margin-right: 0.22222em;">V</span></span></span></span><span
                                        class="vlist-s">​</span></span><span class="vlist-r"><span class="vlist"
                                        style="height: 0.686em;"><span></span></span></span></span></span><span
                            class="mclose nulldelimiter"></span></span><span class="mspace"
                        style="margin-right: 0.2222em;"></span><span class="mbin">×</span><span class="mspace"
                        style="margin-right: 0.2222em;"></span></span><span class="base"><span class="strut"
                        style="height: 0.6595em;"></span><span
                        class="mord mathnormal">i</span></span></span></span></span>
    <p>将 <span class="katex"><span class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML">
                    <semantics>
                        <mrow>
                            <mi>V</mi>
                        </mrow>
                        <annotation encoding="application/x-tex">V</annotation>
                    </semantics>
                </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                        style="height: 0.6833em;"></span><span class="mord mathnormal"
                        style="margin-right: 0.22222em;">V</span></span></span></span> 提出：</p><span
        class="katex-display" ><span class="katex"><span class="katex-mathml"><math
                    xmlns="http://www.w3.org/1998/Math/MathML" display="block">
                    <semantics>
                        <mrow>
                            <mi>T</mi>
                            <mo stretchy="false">(</mo>
                            <mi>V</mi>
                            <mo stretchy="false">)</mo>
                            <mo>=</mo>
                            <mi>V</mi>
                            <mo>×</mo>
                            <munderover>
                                <mo>∑</mo>
                                <mrow>
                                    <mi>i</mi>
                                    <mo>=</mo>
                                    <mn>1</mn>
                                </mrow>
                                <mrow>
                                    <mi>log</mi>
                                    <mo>⁡</mo>
                                    <mi>V</mi>
                                </mrow>
                            </munderover>
                            <mfrac>
                                <mi>i</mi>
                                <msup>
                                    <mn>2</mn>
                                    <mi>i</mi>
                                </msup>
                            </mfrac>
                        </mrow>
                        <annotation encoding="application/x-tex">T(V) = V \times \sum_{i=1}^{\log V} \frac{i}{2^i}
                        </annotation>
                    </semantics>
                </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                        style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                        style="margin-right: 0.13889em;">T</span><span class="mopen">(</span><span
                        class="mord mathnormal" style="margin-right: 0.22222em;">V</span><span
                        class="mclose">)</span><span class="mspace" style="margin-right: 0.2778em;"></span><span
                        class="mrel">=</span><span class="mspace" style="margin-right: 0.2778em;"></span></span><span
                    class="base"><span class="strut" style="height: 0.7667em; vertical-align: -0.0833em;"></span><span
                        class="mord mathnormal" style="margin-right: 0.22222em;">V</span><span class="mspace"
                        style="margin-right: 0.2222em;"></span><span class="mbin">×</span><span class="mspace"
                        style="margin-right: 0.2222em;"></span></span><span class="base"><span class="strut"
                        style="height: 3.1609em; vertical-align: -1.2777em;"></span><span class="mop op-limits"><span
                            class="vlist-t vlist-t2"><span class="vlist-r"><span class="vlist"
                                    style="height: 1.8832em;"><span style="top: -1.8723em; margin-left: 0em;"><span
                                            class="pstrut" style="height: 3.05em;"></span><span
                                            class="sizing reset-size6 size3 mtight"><span class="mord mtight"><span
                                                    class="mord mathnormal mtight">i</span><span
                                                    class="mrel mtight">=</span><span
                                                    class="mord mtight">1</span></span></span></span><span
                                        style="top: -3.05em;"><span class="pstrut"
                                            style="height: 3.05em;"></span><span><span
                                                class="mop op-symbol large-op">∑</span></span></span><span
                                        style="top: -4.3471em; margin-left: 0em;"><span class="pstrut"
                                            style="height: 3.05em;"></span><span
                                            class="sizing reset-size6 size3 mtight"><span class="mord mtight"><span
                                                    class="mop mtight"><span class="mtight">l</span><span
                                                        class="mtight">o</span><span class="mtight"
                                                        style="margin-right: 0.01389em;">g</span></span><span
                                                    class="mspace mtight" style="margin-right: 0.1952em;"></span><span
                                                    class="mord mathnormal mtight"
                                                    style="margin-right: 0.22222em;">V</span></span></span></span></span><span
                                    class="vlist-s">​</span></span><span class="vlist-r"><span class="vlist"
                                    style="height: 1.2777em;"><span></span></span></span></span></span><span
                        class="mspace" style="margin-right: 0.1667em;"></span><span class="mord"><span
                            class="mopen nulldelimiter"></span><span class="mfrac"><span class="vlist-t vlist-t2"><span
                                    class="vlist-r"><span class="vlist" style="height: 1.3365em;"><span
                                            style="top: -2.314em;"><span class="pstrut"
                                                style="height: 3em;"></span><span class="mord"><span class="mord"><span
                                                        class="mord">2</span><span class="msupsub"><span
                                                            class="vlist-t"><span class="vlist-r"><span class="vlist"
                                                                    style="height: 0.7507em;"><span
                                                                        style="top: -2.989em; margin-right: 0.05em;"><span
                                                                            class="pstrut"
                                                                            style="height: 2.7em;"></span><span
                                                                            class="sizing reset-size6 size3 mtight"><span
                                                                                class="mord mathnormal mtight">i</span></span></span></span></span></span></span></span></span></span><span
                                            style="top: -3.23em;"><span class="pstrut" style="height: 3em;"></span><span
                                                class="frac-line"
                                                style="border-bottom-width: 0.04em;"></span></span><span
                                            style="top: -3.677em;"><span class="pstrut"
                                                style="height: 3em;"></span><span class="mord"><span
                                                    class="mord mathnormal">i</span></span></span></span><span
                                        class="vlist-s">​</span></span><span class="vlist-r"><span class="vlist"
                                        style="height: 0.686em;"><span></span></span></span></span></span><span
                            class="mclose nulldelimiter"></span></span></span></span></span></span>
    <p>这个求和公式的结果是一个收敛的常数（大约是 2）。因此，整个堆构建过程的总时间复杂度为：</p><span class="katex-display"><span class="katex"><span
                class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML" display="block">
                    <semantics>
                        <mrow>
                            <mi>T</mi>
                            <mo stretchy="false">(</mo>
                            <mi>V</mi>
                            <mo stretchy="false">)</mo>
                            <mo>=</mo>
                            <mi>O</mi>
                            <mo stretchy="false">(</mo>
                            <mi>V</mi>
                            <mo stretchy="false">)</mo>
                        </mrow>
                        <annotation encoding="application/x-tex">T(V) = O(V)</annotation>
                    </semantics>
                </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                        style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                        style="margin-right: 0.13889em;">T</span><span class="mopen">(</span><span
                        class="mord mathnormal" style="margin-right: 0.22222em;">V</span><span
                        class="mclose">)</span><span class="mspace" style="margin-right: 0.2778em;"></span><span
                        class="mrel">=</span><span class="mspace" style="margin-right: 0.2778em;"></span></span><span
                    class="base"><span class="strut" style="height: 1em; vertical-align: -0.25em;"></span><span
                        class="mord mathnormal" style="margin-right: 0.02778em;">O</span><span
                        class="mopen">(</span><span class="mord mathnormal"
                        style="margin-right: 0.22222em;">V</span><span
                        class="mclose">)</span></span></span></span></span>
    <h3>4. 直观解释</h3>
    <p>虽然每个节点最多需要 <span class="katex"><span class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML">
                    <semantics>
                        <mrow>
                            <mi>log</mi>
                            <mo>⁡</mo>
                            <mi>V</mi>
                        </mrow>
                        <annotation encoding="application/x-tex">\log V</annotation>
                    </semantics>
                </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                        style="height: 0.8889em; vertical-align: -0.1944em;"></span><span class="mop">lo<span
                            style="margin-right: 0.01389em;">g</span></span><span class="mspace"
                        style="margin-right: 0.1667em;"></span><span class="mord mathnormal"
                        style="margin-right: 0.22222em;">V</span></span></span></span>
        步的下滤操作，但只有非常少的节点需要执行这么多步（比如只有根节点需要 <span class="katex"><span class="katex-mathml"><math
                    xmlns="http://www.w3.org/1998/Math/MathML">
                    <semantics>
                        <mrow>
                            <mi>log</mi>
                            <mo>⁡</mo>
                            <mi>V</mi>
                        </mrow>
                        <annotation encoding="application/x-tex">\log V</annotation>
                    </semantics>
                </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                        style="height: 0.8889em; vertical-align: -0.1944em;"></span><span class="mop">lo<span
                            style="margin-right: 0.01389em;">g</span></span><span class="mspace"
                        style="margin-right: 0.1667em;"></span><span class="mord mathnormal"
                        style="margin-right: 0.22222em;">V</span></span></span></span>
        步）。大部分节点的高度较低，因此下滤的代价也较低。由于这种代价逐渐减小，最终总时间复杂度为 <span class="katex"><span class="katex-mathml"><math
                    xmlns="http://www.w3.org/1998/Math/MathML">
                    <semantics>
                        <mrow>
                            <mi>O</mi>
                            <mo stretchy="false">(</mo>
                            <mi>V</mi>
                            <mo stretchy="false">)</mo>
                        </mrow>
                        <annotation encoding="application/x-tex">O(V)</annotation>
                    </semantics>
                </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                        style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                        style="margin-right: 0.02778em;">O</span><span class="mopen">(</span><span
                        class="mord mathnormal" style="margin-right: 0.22222em;">V</span><span
                        class="mclose">)</span></span></span></span>。</p>
    <h3>总结</h3>
    <p>构建最小二叉堆的时间复杂度是 <span class="katex"><span class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML">
                    <semantics>
                        <mrow>
                            <mi>O</mi>
                            <mo stretchy="false">(</mo>
                            <mi>V</mi>
                            <mo stretchy="false">)</mo>
                        </mrow>
                        <annotation encoding="application/x-tex">O(V)</annotation>
                    </semantics>
                </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                        style="height: 1em; vertical-align: -0.25em;"></span><span class="mord mathnormal"
                        style="margin-right: 0.02778em;">O</span><span class="mopen">(</span><span
                        class="mord mathnormal" style="margin-right: 0.22222em;">V</span><span
                        class="mclose">)</span></span></span></span>，原因在于虽然个别节点的下滤代价与堆的高度 <span class="katex"><span
                class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML">
                    <semantics>
                        <mrow>
                            <mi>log</mi>
                            <mo>⁡</mo>
                            <mi>V</mi>
                        </mrow>
                        <annotation encoding="application/x-tex">\log V</annotation>
                    </semantics>
                </math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut"
                        style="height: 0.8889em; vertical-align: -0.1944em;"></span><span class="mop">lo<span
                            style="margin-right: 0.01389em;">g</span></span><span class="mspace"
                        style="margin-right: 0.1667em;"></span><span class="mord mathnormal"
                        style="margin-right: 0.22222em;">V</span></span></span></span>
        有关，但大多数节点的下滤操作代价较小，总的计算成本是一个线性复杂度。</p>
</div>
